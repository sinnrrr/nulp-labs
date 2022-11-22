import Ajv, { JTDDataType } from "ajv/dist/jtd"
import { capitalize } from "."

const carSchema = {
  elements: {
    properties: {
      key: { type: "int32" },
      brand: { type: "string" },
      model: { type: "string" },
      autoType: { enum: ["Passenger car", "Lorry"] },
      capacity: { type: "uint32" },
      fuelConsumption: { type: "uint32" },
      fuelTankVolume: { type: "uint32" },
    },
    optionalProperties: {},
  },
} as const

export type Car = JTDDataType<typeof carSchema>[number]

export type CarsValidatorReturnType = Array<{
  message: string
  meta: string
}>

export const customCarValidators: Partial<
  Record<keyof Car, (s: Car) => string[]>
> = {
  // grades: (r) => {
  //   const messages = []
  //   const has_not_number = r.grades.some((g) => !/^-?\d+$/.test(g.toString()))
  //   const out_of_range = r.grades.map(Number).some((m) => m < 1 || m > 5)
  //   if (has_not_number) messages.push(`Grades must be coma separated numbers`)
  //   if (out_of_range) messages.push(`Grade must be in range of 1-5`)
  //   return messages
  // },
} as const

const ajv = new Ajv({ allErrors: true })
export const carsSerializer = ajv.compileSerializer<Car[]>(carSchema)
const _compiledValidator = ajv.compile<Car[]>(carSchema)

export const carsValidator = (cars: Car[]): CarsValidatorReturnType => {
  _compiledValidator(cars)

  const errors: CarsValidatorReturnType =
    _compiledValidator.errors?.map((e) => ({
      message: e.message
        ? `${capitalize(e.keyword)} error: ${capitalize(e.message)}`
        : "Error",
      meta: `at ${e.instancePath}`,
    })) || []

  cars.forEach((car) =>
    Object.entries(customCarValidators).map(
      ([propertyName, propertyValidator]) => {
        errors.push(
          ...propertyValidator(car).map((e) => ({
            message: e,
            meta: `at ${propertyName} of ${JSON.stringify(car)}`,
          }))
        )
      }
    )
  )

  return errors
}
