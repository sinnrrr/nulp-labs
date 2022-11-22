import { SaveOutlined } from "@ant-design/icons"
import { Button, message } from "antd"
import { useMemo } from "react"
import { carsPersistor } from "../utils"
import { Car } from "../utils/schemas"

interface Props {
  cars: Car[]
}

export const DownloadCarsInfo: React.FC<Props> = ({ cars }) => {
  const carsFile = useMemo(
    () => carsPersistor.generateDownloadLink(cars),
    [cars]
  )

  return (
    <Button
      icon={<SaveOutlined />}
      download="cars.json"
      title="Save cars to file"
      onClick={() => {
        if (!cars.length) message.warn("There is nothing to save")
      }}
      href={carsFile}
    >
      Save
    </Button>
  )
}
