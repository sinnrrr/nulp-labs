import { Alert, Modal, Paper, Snackbar, Table, TableBody, TableCell, TableContainer, TableHead, TableRow } from "@mui/material"
import { useRef } from "react"
import { useDisclosure } from "react-use-disclosure"
import { z } from "zod"
import { useStudentsContext } from "../contexts/students"
import { StudentSchema } from "../schemas/student"
import { LoadDataFileButton } from "./LoadDataFileButton"

export const LoadStudentsFileButton = ({ children }: { children?: React.ReactNode }) => {
  const { setStudents } = useStudentsContext()
  const validationErrors = useRef<z.ZodError | null>(null)
  const validationModalDisclosure = useDisclosure();
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
        validationModalDisclosure.open()
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

    <Modal
      open={validationModalDisclosure.isOpen}
      onClose={validationModalDisclosure.close}
    >
      <TableContainer component={Paper}>
        <Table sx={{ minWidth: 650 }} size="small" aria-label="a dense table">
          <TableHead>
            <TableRow>
              <TableCell sx={{ width: 0 }}>Code</TableCell>
              <TableCell sx={{ width: 0 }}>Expected</TableCell>
              <TableCell sx={{ width: 0 }}>Received</TableCell>
              <TableCell sx={{ width: 0 }}>Element</TableCell>
              <TableCell sx={{ width: 0 }}>Field</TableCell>
              <TableCell>Message</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {validationErrors.current?.errors.map((error) => (
              <TableRow
                sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
              >
                <TableCell>{error.code}</TableCell>
                <TableCell>{(error as any).expected}</TableCell>
                <TableCell>{(error as any).received}</TableCell>
                <TableCell>{error.path[0]}</TableCell>
                <TableCell>{error.path[1]}</TableCell>
                <TableCell>{error.message}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </Modal>

    <LoadDataFileButton onSubmit={onStudentsFileLoaded} onError={onFileOpenError}>{children}</LoadDataFileButton>
  </>)
}
