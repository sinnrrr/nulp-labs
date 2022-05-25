import { Box } from '@mui/material';
import { DataGrid, GridColDef, GridValueGetterParams } from '@mui/x-data-grid';
import type { NextPage } from 'next';

const rows = [
  { id: 1, firstName: "Dmytro", lastName: "Soltysiuk", grades: [4, 5, 6], birthDate: Date.now() },
  { id: 2, firstName: "Dmytro", lastName: "Soltysiuk", grades: [6, 3, 6], birthDate: Date.now() },
];

const average = (arr: number[]) => arr.reduce((p, c) => p + c, 0) / arr.length;

const columns: GridColDef[] = [
  { field: 'firstName', headerName: 'First name' },
  { field: 'lastName', headerName: 'Last name' },
  {
    field: 'grades',
    headerName: 'Grades',
  },
  {
    field: 'gradesAverage',
    headerName: 'Grades',
    type: 'number',
    valueGetter: (params: GridValueGetterParams) => average(params.row.grades)
  },
  {
    field: 'birthDate',
    headerName: 'Birth date',
  },
];

const Home: NextPage = () => {
  return (
    <Box sx={{ display: 'flex', minHeight: '100vh', flexGrow: 1 }}>
      <Box sx={{ display: 'flex', flexGrow: 1 }}>
        <DataGrid
          rows={rows}
          columns={columns}
          pageSize={5}
          rowsPerPageOptions={[5]}
          checkboxSelection
        />
      </Box>
    </Box>
  )
}

export default Home
