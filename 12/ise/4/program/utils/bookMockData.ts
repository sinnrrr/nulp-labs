import { generateMock } from "@anatine/zod-mock";
import { faker } from "@faker-js/faker";
import { BookSchema } from "../schemas/book";

export const bookMockData = () => generateMock(BookSchema, {
  stringMap: {
    author: () => `${faker.name.firstName()} ${faker.name.lastName()}`,
    name: faker.animal.cow,
    publishedAt: () => faker.date.past(100) as unknown as string
  }
})
