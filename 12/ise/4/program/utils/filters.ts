import { Book, BookFilter } from "../schemas/book";

export const filters: { [key in BookFilter]: (input: Book[]) => Book[] } = {
  publishedEarlier1975: (books) => books.filter((book) => book.publishedAt.getFullYear() < 1975),
  excludePublishedWithinLast5Years: (books) => books.filter((book) => book.publishedAt.getFullYear() > (new Date()).getFullYear() - 50)
}
