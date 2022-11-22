import { RcFile } from "antd/lib/upload"
import {
  Car,
  carsSerializer,
  carsValidator,
  CarsValidatorReturnType,
} from "./schemas"
import { message, notification } from "antd"

export const capitalize = (s: any) => {
  if (typeof s !== "string") return ""
  return s.charAt(0).toUpperCase() + s.slice(1)
}

export const MIN = 0
export const MAX = 1

type FuelConsumptionExtrema = {
  [brand: string]: [number, number]
}

export class CarsUtils {
  static capacityExtrema(
    cars: Car[],
    carTypeRequired?: Car["autoType"]
  ): [Car, Car] {
    if (carTypeRequired) {
      cars = cars.filter((car) => car.autoType === carTypeRequired)
    }

    const extrema = cars.slice(1, -1).reduce(
      (acc: [Car, Car], curr) => {
        acc[0] =
          acc[0] === undefined || curr.capacity < acc[0].capacity
            ? curr
            : acc[0]
        acc[1] =
          acc[1] === undefined || curr.capacity > acc[1].capacity
            ? curr
            : acc[1]

        return acc
      },
      [cars[0], cars[cars.length - 1]]
    )

    return extrema
  }

  static fuelConsumptionExtremaByBrand(cars: Car[]): FuelConsumptionExtrema {
    const brandsFuelConsumption: FuelConsumptionExtrema = {}

    for (let car of cars) {
      if (!brandsFuelConsumption[car.brand]) {
        brandsFuelConsumption[car.brand] = [
          Number.POSITIVE_INFINITY,
          Number.NEGATIVE_INFINITY,
        ]
      }

      const [min, max] = brandsFuelConsumption[car.brand]
      brandsFuelConsumption[car.brand][MIN] =
        car.fuelConsumption < min ? car.fuelConsumption : min
      brandsFuelConsumption[car.brand][MAX] =
        car.fuelConsumption > max ? car.fuelConsumption : max
    }

    return brandsFuelConsumption
  }

  static brandsWithBothVehicleTypes(cars: Car[]): string[] {
    const PASSANGER_CARS = 0
    const LORRIES = 1

    const proxy: { [x in Car["autoType"]]: number } = {
      Lorry: LORRIES,
      "Passenger car": PASSANGER_CARS,
    }

    const intermediateBrandsArr: { [brand: string]: [boolean, boolean] } = {}

    for (let car of cars) {
      if (!intermediateBrandsArr[car.brand]) {
        intermediateBrandsArr[car.brand] = [false, false]
      }

      intermediateBrandsArr[car.brand][proxy[car.autoType]] = true
    }

    return Object.entries(intermediateBrandsArr)
      .map(([brand, autoTypes]) => {
        if (autoTypes[PASSANGER_CARS] && autoTypes[LORRIES]) {
          return brand
        }
      })
      .filter(Boolean) as string[]
  }
}

class CarsPersister {
  generateDownloadLink(cars: Car[]) {
    if (!cars.length) return

    const raw = carsSerializer(cars)
    return URL.createObjectURL(
      new Blob([raw], {
        type: "application/json",
      })
    )
  }

  loadFromFile(file: RcFile, onLoad: (cars: Car[]) => void) {
    const reader = new FileReader()
    reader.readAsText(file)
    reader.onload = () => {
      const raw = reader.result?.toString() || "[]"
      let cars: Car[] = []
      let errors: CarsValidatorReturnType = []

      try {
        cars = JSON.parse(raw)
      } catch (e) {
        if (e instanceof Error) {
          errors.push({
            message: `File is corrupted (wrong json)`,
            meta: e.message,
          })
        }
      }
      errors.push(...carsValidator(cars))

      if (errors?.length) {
        errors.forEach((e) =>
          notification.error({
            message: `${e.message}`,
            description: `Please fix the detected error: ${e.meta}`,
            placement: "bottomLeft",
            duration: 30,
          })
        )
      }

      if (cars.length) {
        onLoad(cars)
        message.success(`Loaded cars from ${file.name}`)
      } else {
        message.info(`File ${file.name} was emtpy`)
      }
    }
  }
}

export const carsPersistor = new CarsPersister()

export const generateExtremaFuelConsumptionDesc = (
  extrema: FuelConsumptionExtrema
) => {
  let compiled = ""

  for (const [brand, [min, max]] of Object.entries(extrema)) {
    compiled += `${brand} (min: ${min}, max: ${max}), `
  }

  return compiled.slice(0, -2)
}
