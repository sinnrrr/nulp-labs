import { SaveOutlined } from "@ant-design/icons"
import { Button, message } from "antd"
import { carsPersistor } from "../utils"
import { Car } from "../utils/schemas"

interface Props {
  cars: Car[]
}

export const DownloadCarsInfo: React.FC<Props> = ({ cars }) => {
  return (
    <Button
      icon={<SaveOutlined />}
      download="cars.json"
      title="Save cars to file"
      onClick={() => {
        if (!cars.length) message.warn("There is nothing to save")
        carsPersistor.downloadCarsFile(cars)
      }}
    >
      Save
    </Button>
  )
}
