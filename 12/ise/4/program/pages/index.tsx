import AddCircleIcon from "@mui/icons-material/AddCircle";
import DocumentScannerIcon from "@mui/icons-material/DocumentScanner";
import {
  Box,
  Button,
  Checkbox,
  FormControlLabel,
  FormGroup,
  IconButton,
  Pagination,
  Stack,
  Typography,
} from "@mui/material";
import {
  DataGrid,
  GridColDef,
  gridPageCountSelector,
  gridPageSelector,
  GridToolbar,
  useGridApiContext,
  useGridSelector,
} from "@mui/x-data-grid";
import type { NextPage } from "next";
import { LoadBooksFileButton } from "../components/LoadBooksFileButton";
import { useBooksContext } from "../contexts/books";
import { Book, BookSchema } from "../schemas/book";
import { bookMockData } from "../utils/bookMockData";
import { FieldParser } from "../utils/fieldParser";

const fieldParser = FieldParser(BookSchema);
const columns: GridColDef<Book>[] = [
  {
    field: "name",
    headerName: "Book name",
    editable: true,
    width: 150,
    preProcessEditCellProps: fieldParser("name"),
  },
  {
    field: "author",
    headerName: "Author",
    editable: true,
    width: 150,
    preProcessEditCellProps: fieldParser("author"),
  },
  {
    field: "price",
    headerName: "Price",
    type: "number",
    editable: true,
    sortingOrder: ["desc"],
    preProcessEditCellProps: fieldParser("price"),
  },
  {
    field: "pagesCount",
    headerName: "Pages",
    type: "number",
    editable: true,
    preProcessEditCellProps: fieldParser("pagesCount"),
  },
  {
    field: "publishedAt",
    headerName: "Publish date",
    type: "date",
    width: 230,
    editable: true,
    preProcessEditCellProps: fieldParser("publishedAt"),
    valueParser: (value: Date) => value.toUTCString(),
    valueGetter: (params) => new Date(Date.parse(params.value)),
  },
];

const CustomFilterPanel = () => {
  const { setFilter, enabledFilters, books } = useBooksContext();

  return (
    <FormGroup>
      <FormControlLabel
        label="Published earlier 1975"
        control={
          <Checkbox
            disabled={books === null || books.length === 0}
            checked={enabledFilters.publishedEarlier1975}
            onChange={(e) =>
              setFilter("publishedEarlier1975", e.target.checked)
            }
          />
        }
      />

      <FormControlLabel
        label="Exclude published within last 50 years"
        control={
          <Checkbox
            disabled={books === null || books.length === 0}
            checked={enabledFilters.excludePublishedWithinLast50Years}
            onChange={(e) =>
              setFilter("excludePublishedWithinLast50Years", e.target.checked)
            }
          />
        }
      />
    </FormGroup>
  );
};

const CustomPagination = () => {
  const apiRef = useGridApiContext();
  const page = useGridSelector(apiRef, gridPageSelector);
  const pageCount = useGridSelector(apiRef, gridPageCountSelector);
  const { booksDataString, addBook } = useBooksContext();

  const handleAddBookButtonClick = () => {
    addBook(bookMockData());
  };

  const hasRows = apiRef.current.getRowsCount() > 0;
  if (!hasRows) return null;

  return (
    <Stack
      direction="row"
      sx={{
        display: "flex",
        padding: 1,
        flexGrow: 1,
        width: "100%",
        justifyContent: "space-between",
        alignItems: "center",
      }}
    >
      <Stack direction="row" spacing={1}>
        <IconButton color="primary" onClick={handleAddBookButtonClick}>
          <AddCircleIcon fontSize="large" />
        </IconButton>

        <LoadBooksFileButton>Load</LoadBooksFileButton>

        {/* @ts-ignore */}
        <Button
          variant="outlined"
          href={booksDataString || undefined}
          download="books.json"
        >
          Save
        </Button>
      </Stack>

      <Pagination
        color="primary"
        count={pageCount}
        page={page + 1}
        onChange={(_event, value) => apiRef.current.setPage(value - 1)}
      />
    </Stack>
  );
};

const CustomNoRowsOverlay = () => (
  <Stack spacing={2} height="100%" alignItems="center" justifyContent="center">
    <DocumentScannerIcon
      sx={{ width: { xs: "20%", sm: "15%", md: "10%" }, height: "auto" }}
    />
    <Typography>No data provided</Typography>
    <Stack direction="row">
      <LoadBooksFileButton>Load data</LoadBooksFileButton>
    </Stack>
  </Stack>
);

const Home: NextPage = () => {
  const { filteredBooks, books, setBooks } = useBooksContext();
  const elementsPerPage = 20;

  return (
    <Box sx={{ display: "flex", minHeight: "100vh", flexGrow: 1 }}>
      <Box sx={{ display: "flex", flexGrow: 1, width: "100%" }}>
        <DataGrid
          experimentalFeatures={{ newEditingApi: true }}
          rows={filteredBooks || books || []}
          columns={columns}
          pageSize={elementsPerPage}
          rowsPerPageOptions={[elementsPerPage]}
          processRowUpdate={(data) => {
            const booksCopy = [...(filteredBooks || [])];
            const changedBookIndex = booksCopy.findIndex(
              (el) => el.id === data.id
            );

            booksCopy[changedBookIndex] = data;
            setBooks(booksCopy);

            return data;
          }}
          components={{
            Pagination: CustomPagination,
            NoRowsOverlay: CustomNoRowsOverlay,
            Toolbar: GridToolbar,
            FilterPanel: CustomFilterPanel,
          }}
        />
      </Box>
    </Box>
  );
};

export default Home;
