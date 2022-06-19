import { Alert, Button, Dialog, DialogActions, DialogContent, DialogTitle, Paper, Snackbar, Table, TableBody, TableCell, TableContainer, TableHead, TableRow } from "@mui/material"
import { styled } from '@mui/material/styles'
import { tableCellClasses } from '@mui/material/TableCell'
import * as React from 'react'
import { useRef } from "react"
import { useDisclosure } from "react-use-disclosure"
import { z } from "zod"
import { useStudentsContext } from "../contexts/students"
import { StudentSchema } from "../schemas/student"
import { LoadDataFileButton } from "./LoadDataFileButton"

const StyledTableCell = styled(TableCell)(({ theme }) => ({
  [`&.${tableCellClasses.head}`]: {
    backgroundColor: theme.palette.error.light,
    color: theme.palette.common.white,
  },
  [`&.${tableCellClasses.body}`]: {
    fontSize: 14,
  },
}));

const StyledTableRow = styled(TableRow)(({ theme }) => ({
  '&:nth-of-type(odd)': {
    backgroundColor: theme.palette.action.hover,
  },
  // hide last border
  '&:last-child td, &:last-child th': {
    border: 0,
  },
}));

export const LoadStudentsFileButton = ({ children }: { children?: React.ReactNode }) => {
  const { setStudents } = useStudentsContext()
  const validationErrors = useRef<z.ZodError | null>(null)
  const validationDialogDisclosure = useDisclosure();
  const fileEmptyDisclosure = useDisclosure();
  const fileOpenErrorDisclosure = useDisclosure();
  const successSnackbarDisclosure = useDisclosure();

  const onStudentsFileLoaded = async (rawStudentsData: string) => {
    const rawStudents = JSON.parse(rawStudentsData)

    if (rawStudents.length === 0) {
      fileEmptyDisclosure.open()
      return;
    }

    await z.array(StudentSchema).parseAsync(rawStudents)
      .then((students) => {
        setStudents(students)
        successSnackbarDisclosure.open()
      }).catch((errors) => {
        validationErrors.current = errors
        validationDialogDisclosure.open()
      })
  }

  const onFileOpenError = () => {
    fileOpenErrorDisclosure.open()
  }

  return (<>
    <Snackbar
      autoHideDuration={3000}
      open={successSnackbarDisclosure.isOpen}
      onClose={successSnackbarDisclosure.close}
    >
      <Alert onClose={successSnackbarDisclosure.close} severity="success" sx={{ width: '100%' }}>
        Successfully opened file
      </Alert>
    </Snackbar>

    <Snackbar
      autoHideDuration={3000}
      open={fileEmptyDisclosure.isOpen}
      onClose={fileEmptyDisclosure.close}
    >
      <Alert onClose={fileEmptyDisclosure.close} severity="warning" sx={{ width: '100%' }}>
        File is empty
      </Alert>
    </Snackbar>

    <Snackbar
      autoHideDuration={3000}
      open={fileOpenErrorDisclosure.isOpen}
      onClose={fileOpenErrorDisclosure.close}
    >
      <Alert onClose={fileOpenErrorDisclosure.close} severity="error" sx={{ width: '100%' }}>
        File failed to open due to system error
      </Alert>
    </Snackbar>

    <Dialog
      open={validationDialogDisclosure.isOpen}
      onClose={validationDialogDisclosure.close}
    >
      <DialogTitle>There is few validation errors</DialogTitle>

      <DialogContent>
        <TableContainer component={Paper} >
          <Table sx={{ minWidth: 650 }} size="small" aria-label="a dense table">
            <TableHead>
              <TableRow>
                <StyledTableCell sx={{ width: 0 }}>Code</StyledTableCell>
                <StyledTableCell sx={{ width: 0 }}>Expected</StyledTableCell>
                <StyledTableCell sx={{ width: 0 }}>Received</StyledTableCell>
                <StyledTableCell sx={{ width: 0 }}>Element</StyledTableCell>
                <StyledTableCell sx={{ width: 0 }}>Field</StyledTableCell>
                <StyledTableCell>Message</StyledTableCell>
              </TableRow>
            </TableHead>
            <TableBody>
              {validationErrors.current?.errors.map((error) => (
                <StyledTableRow
                  sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                >
                  <StyledTableCell>{error.code}</StyledTableCell>
                  <StyledTableCell>{(error as any).expected}</StyledTableCell>
                  <StyledTableCell>{(error as any).received}</StyledTableCell>
                  <StyledTableCell>{error.path[0]}</StyledTableCell>
                  <StyledTableCell>{error.path[1]}</StyledTableCell>
                  <StyledTableCell>{error.message}</StyledTableCell>
                </StyledTableRow>
              ))}
            </TableBody>
          </Table>
        </TableContainer>
      </DialogContent>

      <DialogActions>
        <Button onClick={validationDialogDisclosure.close} autoFocus>
          Gotcha
        </Button>
      </DialogActions>
    </Dialog>

    <LoadDataFileButton onSubmit={onStudentsFileLoaded} onError={onFileOpenError}>{children}</LoadDataFileButton>
  </>)
}
