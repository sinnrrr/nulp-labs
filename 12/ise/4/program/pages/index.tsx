import AddCircleIcon from '@mui/icons-material/AddCircle';
import DocumentScannerIcon from '@mui/icons-material/DocumentScanner';
import { Box, Button, IconButton, Pagination, Stack, Typography } from '@mui/material';
import { DataGrid, getGridDefaultColumnTypes, GridCellParams, GridColDef, GridFilterItem, GridFilterOperator, gridPageCountSelector, gridPageSelector, GridStateColDef, GridValueGetterParams, useGridApiContext, useGridSelector } from '@mui/x-data-grid';
import { randFirstName, randLastName, randNumber, randPastDate } from '@ngneat/falso';
import type { NextPage } from 'next';
import { LoadStudentsFileButton } from '../components/LoadStudentsFileButton';
import { useStudentsContext } from "../contexts/students";
import { Student } from '../schemas/student';
import { averageNumber } from '../utils/averageNumber';

const wrapOperator = (operator: GridFilterOperator) => {
  const getApplyFilterFn = (
    filterItem: GridFilterItem,
    column: GridStateColDef,
  ) => {
    const innerFilterFn = operator.getApplyFilterFn(filterItem, column);
    if (!innerFilterFn) {
      return innerFilterFn;
    }

    return (params: GridCellParams) => {
      return !innerFilterFn(params);
    };
  };

  return {
    ...operator,
    getApplyFilterFn,
    label: 'excludes',
    value: 'excludes',
  };
};

const gridStringColumnDefaults = getGridDefaultColumnTypes().string
const notContainsOperator = wrapOperator(gridStringColumnDefaults.filterOperators!.filter(f => f.value === "contains")[0])
gridStringColumnDefaults.filterOperators!.unshift(notContainsOperator)

const columns: GridColDef<Student>[] = [
  { field: 'firstName', headerName: 'First name' },
  { field: 'lastName', headerName: 'Last name' },
  {
    field: 'grades',
    headerName: 'Grades',
    filterOperators: gridStringColumnDefaults.filterOperators
  },
  {
    field: 'gradesAverage',
    headerName: 'Average grade',
    valueGetter: (params: GridValueGetterParams) => averageNumber(params.row.grades).toFixed(2)
  },
  {
    field: 'birthDate',
    headerName: 'Birth date',
    width: 230,
    type: 'date',
    valueGetter: (params) => new Date(params.row.birthDate),
    valueFormatter: (params) => params.value.toUTCString()
  },
];

const CustomPagination = () => {
  const apiRef = useGridApiContext();
  const page = useGridSelector(apiRef, gridPageSelector);
  const pageCount = useGridSelector(apiRef, gridPageCountSelector);
  const { studentsDataString, addStudent } = useStudentsContext()

  const handleAddStudentButtonClick = () => {
    addStudent({
      id: randNumber(),
      firstName: randFirstName(),
      lastName: randLastName(),
      grades: randNumber({ min: 1, max: 5, length: 6 }),
      birthDate: +randPastDate()
    })
  }

  const hasRows = apiRef.current.getRowsCount() > 0
  if (!hasRows) return null;

  return (
    <Stack direction="row" sx={{ display: 'flex', padding: 1, flexGrow: 1, width: "100%", justifyContent: "space-between", alignItems: "center" }}>
      <Stack direction="row" spacing={1}>
        <IconButton color="primary" onClick={handleAddStudentButtonClick}>
          <AddCircleIcon fontSize="large" />
        </IconButton>

        <LoadStudentsFileButton>Load</LoadStudentsFileButton>

        {/* @ts-ignore */}
        <Button
          variant='outlined'
          href={studentsDataString || undefined}
          download="students.json"
        >Save</Button>

      </Stack>

      <Pagination
        color="primary"
        count={pageCount}
        page={page + 1}
        onChange={(_event, value) => apiRef.current.setPage(value - 1)}
      />
    </Stack>
  )
}

const CustomNoRowsOverlay = () => (
  <Stack spacing={2} height="100%" alignItems="center" justifyContent="center">
    <DocumentScannerIcon sx={{ width: { xs: "20%", sm: "15%", md: "10%" }, height: "auto" }} />
    <Typography>No data provided</Typography>
    <Stack direction="row">
      <LoadStudentsFileButton>Load data</LoadStudentsFileButton>
    </Stack>
  </Stack>
)

const Home: NextPage = () => {
  const { students } = useStudentsContext()
  const elementsPerPage = 20

  return (
    <Box sx={{ display: 'flex', minHeight: '100vh', flexGrow: 1 }}>
      <Box sx={{ display: 'flex', flexGrow: 1, width: "100%" }}>
        <DataGrid
          rows={students || []}
          columns={columns}
          pageSize={elementsPerPage}
          rowsPerPageOptions={[elementsPerPage]}
          checkboxSelection
          components={{ Pagination: CustomPagination, NoRowsOverlay: CustomNoRowsOverlay }}
        />
      </Box>
    </Box>
  )
}

export default Home
