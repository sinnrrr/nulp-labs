import { Button, Space, Table, Typography } from "antd"
import { Rule } from "antd/lib/form"
import { ColumnsType } from "antd/lib/table"
import React, { Ref, useMemo, useState } from "react"
import {
  CarsUtils,
  generateExtremaFuelConsumptionDesc,
  MAX,
  MIN,
} from "../../utils"
import { mergeSort } from "../../utils/mergeSort"
/* import { mostUsedCar } from "../../utils" */
import { Car } from "../../utils/schemas"
import { DownloadCarsInfo } from "../DownloadCarsInfo"
import { LoadCars } from "../LoadCars"
import { EditableCell } from "./Cell"
import { EditableRow } from "./Row"

const { Text, Title } = Typography

export type CarsTableEditProps = {
  edit?: {
    component?: (save: () => void, ref: Ref<any>) => React.ReactNode
    serialize?: (value: any) => any
    deserialize?: (value: any) => any
    rules?: Rule[]
  }
  dataIndex: keyof Car
}

const columns: Array<ColumnsType<Car>[number] & CarsTableEditProps> = [
  {
    title: "No",
    dataIndex: "key",
  },
  {
    title: "Brand",
    dataIndex: "brand",
    edit: {},
    sorter: (a, b) => a.brand.localeCompare(b.brand),
  },
  {
    title: "Model",
    dataIndex: "model",
    edit: {},
  },
  {
    title: "Type",
    dataIndex: "autoType",
    edit: {},
    filters: ["Passenger car", "Lorry"].map((type) => ({
      text: `Show only "${type}"`,
      value: type,
    })),
    onFilter: (value, record) => record.autoType == value,
  },
  {
    title: "Capacity",
    dataIndex: "capacity",
    edit: {},
  },
  {
    title: "Fuel consumption",
    dataIndex: "fuelConsumption",
    edit: {},
    sorter: (a, b) => a.fuelConsumption - b.fuelConsumption,
  },
  {
    title: "Fuel tank volume",
    dataIndex: "fuelTankVolume",
    edit: {},
    sorter: (a, b) => {
      const durability = (car: Car) => car.fuelTankVolume / car.fuelConsumption
      return durability(a) - durability(b)
    },
  },
]

export const CarsTable: React.FC = () => {
  const [cars, setCars] = useState<Car[]>([])

  const handleAdd = () => {
    setCars((s) => [
      ...s,
      {
        key: s.length,
        brand: "Unknown",
        model: "Unknown",
        autoType: "Passenger car",
        capacity: 0,
        fuelConsumption: 0,
        fuelTankVolume: 0,
      },
    ])
  }

  const handleSave = (row: Car) => {
    const newCars = [...cars]
    const index = newCars.findIndex((car) => row.key === car.key)
    newCars.splice(index, 1, {
      ...newCars[index],
      ...row,
    })
    setCars(newCars)
  }

  const uicolumns = columns.map((col) => {
    if (!col.edit) return col

    return {
      ...col,
      onCell: (record: Car) => ({
        record,
        edit: col.edit,
        dataIndex: col.dataIndex,
        title: col.title,
        handleSave,
      }),
    }
  })

  const mostPowerfulPassengerCar = CarsUtils.capacityExtrema(
    cars,
    "Passenger car"
  )[MAX]
  const leastPowerfulLorry = CarsUtils.capacityExtrema(cars, "Lorry")[MIN]
  const brandsWithBothCarTypes = CarsUtils.brandsWithBothVehicleTypes(cars)
  const fuelConsumptionExtrema = CarsUtils.fuelConsumptionExtremaByBrand(cars)

  return (
    <Space direction="vertical" size="middle" style={{ display: "flex" }}>
      <Space size="middle">
        <LoadCars onCars={setCars} />
        <DownloadCarsInfo cars={cars} />
        <Button onClick={handleAdd} type="primary" title="Add car entry">
          Add
        </Button>
      </Space>

      {/* {mostUsed && ( */}
      {/*   <Statistic */}
      {/*     title={`${mostUsed.ticketType} car is the most used`} */}
      {/*     value={mostUsed.count} */}
      {/*   /> */}
      {/* )} */}

      <Table<Car>
        bordered
        dataSource={cars}
        columns={uicolumns as typeof columns}
        pagination={{
          pageSizeOptions: [2, 10, 30, 50, 100],
          defaultPageSize: 30,
        }}
        components={{
          body: {
            row: EditableRow,
            cell: EditableCell,
          },
        }}
        rowClassName={() => "editable-row"}
      />

      {cars.length > 0 && (
        <div style={{ display: "flex", flexDirection: "column" }}>
          <Title level={3}>Statistics</Title>

          <Space direction="vertical" size="middle" style={{ display: "flex" }}>
            <Text strong>
              The most powerful passanger car is{" "}
              <Text underline>
                {mostPowerfulPassengerCar.brand}{" "}
                {mostPowerfulPassengerCar.model}
              </Text>{" "}
              and the least powerful lorry is{" "}
              <Text underline>
                {leastPowerfulLorry.brand} {leastPowerfulLorry.model}
              </Text>
            </Text>

            <div style={{ display: "flex", flexDirection: "column" }}>
              <Text strong>Auto brands that have both types of vehicles:</Text>
              <Text>{brandsWithBothCarTypes.join(", ")}</Text>
            </div>

            <div style={{ display: "flex", flexDirection: "column" }}>
              <Text strong>
                Biggest and smallest fuel consumption of each brand:
              </Text>
              <Text>
                {generateExtremaFuelConsumptionDesc(fuelConsumptionExtrema)}
              </Text>
            </div>
          </Space>
        </div>
      )}
    </Space>
  )
}
