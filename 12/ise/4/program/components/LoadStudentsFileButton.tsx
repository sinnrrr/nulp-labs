import { Alert, Modal, Snackbar } from "@mui/material"
import { useState } from "react"
import { useDisclosure } from "react-use-disclosure"
import { z } from "zod"
import { useStudentsContext } from "../contexts/students"
import { StudentSchema } from "../schemas/student"
import { LoadDataFileButton } from "./LoadDataFileButton"

export const LoadStudentsFileButton = ({ children }: { children?: React.ReactNode }) => {
  const { setStudents } = useStudentsContext()
  const [validationErrors, setValidationErrors] = useState<any[] | null>(null)
  const validationModalDisclosure = useDisclosure(validationErrors ? validationErrors.length > 0 : false);
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
      .then(setStudents)
      .catch(setValidationErrors)
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
      <code>{JSON.stringify(validationErrors)}</code>
    </Modal>

    <LoadDataFileButton onSubmit={onStudentsFileLoaded} onError={onFileOpenError}>{children}</LoadDataFileButton>
  </>)
}
