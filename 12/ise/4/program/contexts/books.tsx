import {
  createContext, useContext, useState
} from "react";
import { Book } from "../schemas/book";

type BooksContextType = {
  books: Book[] | null,
  booksDataString: string | null,
  addBook: (book: Book) => void,
  setBooks: (books: Book[]) => void,
};

const defaultValues: BooksContextType = {
  books: null,
  booksDataString: null,
  addBook: () => { },
  setBooks: () => { },
};

const BooksContext = createContext<BooksContextType>(defaultValues);

export const useBooksContext = () => useContext(BooksContext);

export const BooksContextProvider = ({ children }: { children?: React.ReactNode }) => {
  const [books, setBooks] = useState<Book[] | null>(null)

  const addBook = (book: Book) => {
    setBooks([...books || [], book])
  }

  return (
    <BooksContext.Provider value={{
      books: books,
      booksDataString: "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(books)),
      addBook: addBook,
      setBooks: setBooks,
    }}>{children}</BooksContext.Provider>
  );
};
