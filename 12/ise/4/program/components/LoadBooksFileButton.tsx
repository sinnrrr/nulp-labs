import { BookSchema } from "../schemas/book";
import { FunctionComponent } from "../types";
import { LoadValidatedFileButton } from "./LoadValidatedFileButton";

export const LoadBooksFileButton: FunctionComponent = ({ children }) =>
  <LoadValidatedFileButton schema={BookSchema}>{children}</LoadValidatedFileButton>
