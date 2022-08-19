import { createContext, useContext, useEffect, useState } from "react";
import { Book, BookFilter } from "../schemas/book";
import { filters } from "../utils/filters";

type BooksContextType = {
  books: Book[] | null;
  filteredBooks: Book[] | null;
  booksDataString: string | null;
  addBook: (book: Book) => void;
  setBooks: (books: Book[]) => void;
  enabledFilters: { [key in BookFilter]: boolean };
  setFilter: (filter: BookFilter, shouldBeApplied: boolean) => void;
};

const defaultValues: BooksContextType = {
  books: null,
  filteredBooks: null,
  booksDataString: null,
  enabledFilters: {
    publishedEarlier1975: false,
    excludePublishedWithinLast50Years: false,
  },
  addBook: () => {},
  setBooks: () => {},
  setFilter: () => {},
};

const BooksContext = createContext<BooksContextType>(defaultValues);

export const useBooksContext = () => useContext(BooksContext);

export const BooksContextProvider = ({
  children,
}: {
  children?: React.ReactNode;
}) => {
  const [books, setBooks] = useState<BooksContextType["books"]>(
    defaultValues.books
  );
  const [filteredBooks, setFilteredBooks] = useState<
    BooksContextType["filteredBooks"]
  >(defaultValues.filteredBooks);
  const [enabledFilters, setEnabledFilters] = useState<
    BooksContextType["enabledFilters"]
  >(defaultValues.enabledFilters);

  const addBook = (book: Book) => {
    setBooks([...(books || []), book]);
  };

  const setFilter: BooksContextType["setFilter"] = (
    filter,
    shouldBeEnabled
  ) => {
    setEnabledFilters({ ...enabledFilters, [filter]: shouldBeEnabled });
  };

  useEffect(() => {
    if (Object.values(enabledFilters).filter(Boolean).length === 0) {
      setFilteredBooks(books);

      return;
    }

    const filtersResult = Object.entries(enabledFilters)
      .map(([filterName, shouldBeEnabled]) => {
        if (!shouldBeEnabled) return;
        if (books === null || books.length === 0) return;

        return filters[filterName as BookFilter]([...books]);
      })
      .filter(Boolean) as Book[][];

    if (filtersResult.length === 1) {
      setFilteredBooks(filtersResult[0]);

      return;
    }

    // leave only duplicates in array
    const filtered = filtersResult.flat().filter((value, index, self) => {
      return (
        self.map((el) => el.id).indexOf(value.id) === index &&
        self.map((el) => el.id).lastIndexOf(value.id) !== index
      );
    });

    setFilteredBooks(filtered);
  }, [enabledFilters]);

  return (
    <BooksContext.Provider
      value={{
        books: books,
        filteredBooks,
        booksDataString:
          "data:text/json;charset=utf-8," +
          encodeURIComponent(JSON.stringify(books)),
        addBook: addBook,
        setBooks: setBooks,
        enabledFilters,
        setFilter,
      }}
    >
      {children}
    </BooksContext.Provider>
  );
};
