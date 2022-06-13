import { z } from "zod"

const unixEpochMaxValue = 2147483647

export const StudentSchema = z.object({
  id: z.number().min(0),
  firstName: z.string().min(2).max(32),
  lastName: z.string().min(2).max(32),
  grades: z.array(z.number().min(1).max(5)),
  birthDate: z.number().min(0).max(unixEpochMaxValue)
    .or(
      z.string()
        .refine(d => !isNaN(Date.parse(d)))
        .transform((v) => Date.parse(v))
    )
})

export type Student = z.infer<typeof StudentSchema>
