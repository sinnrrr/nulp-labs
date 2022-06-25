import { z } from "zod";

export const BookSchema = z.object({
  id: z.number().nonnegative(),
  name: z.string().min(2).max(32),
  author: z.string().min(2).max(32),
  price: z
    .number()
    .nonnegative()
    .max(10 * 100),
  pagesCount: z
    .number()
    .min(1)
    .max(10 * 100),
  publishedAt: z
    .string()
    .refine((d) => !isNaN(Date.parse(d)))
    .transform((v) => new Date(Date.parse(v))),
});

export type Book = z.infer<typeof BookSchema>;
export type BookFilter =
  | "publishedEarlier1975"
  | "excludePublishedWithinLast50Years";
