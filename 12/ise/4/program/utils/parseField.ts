import { GridPreProcessEditCellProps } from "@mui/x-data-grid"
import { z } from "zod"
import { StudentSchema } from "../schemas/student"

export const parseField = (field: keyof z.infer<typeof StudentSchema>) => {
  return (params: GridPreProcessEditCellProps) => {
    const data = StudentSchema.shape[field].safeParse(params.props.value)
    const hasErrors = !data.success

    return { ...params.props, error: hasErrors }
  }
}
