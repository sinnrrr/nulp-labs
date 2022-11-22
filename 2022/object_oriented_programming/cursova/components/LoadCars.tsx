import { FileSearchOutlined } from "@ant-design/icons"
import { Button, Upload } from "antd"
import { carsPersistor } from "../utils"
import { Car } from "../utils/schemas"

interface Props {
  onCars: (cars: Car[]) => void
}

export const LoadCars: React.FC<Props> = ({ onCars }) => {
  return (
    <Upload
      accept=".json"
      beforeUpload={(file) => carsPersistor.loadFromFile(file, onCars)}
      showUploadList={false}
    >
      <Button
        icon={<FileSearchOutlined />}
        title="Load cars from selected file"
      >
        Load
      </Button>
    </Upload>
  )
}
