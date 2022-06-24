import { GridPreProcessEditCellProps } from "@mui/x-data-grid";
import { z } from "zod";

export const FieldParser = <T extends z.ZodRawShape>(schema: z.ZodObject<T>) =>
  (field: keyof z.infer<typeof schema>) => (params: GridPreProcessEditCellProps) => {
    const data = schema.shape[field].safeParse(params.props.value)
    const hasErrors = !data.success

    return { ...params.props, error: hasErrors }
  }
