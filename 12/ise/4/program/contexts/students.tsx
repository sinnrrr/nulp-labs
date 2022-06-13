import {
  createContext, useContext, useState
} from "react";
import { Student } from "../schemas/student";

type StudentsContextType = {
  students: Student[] | null,
  addStudent: (student: Student) => void,
  setStudents: (students: Student[]) => void,
};

const defaultValues: StudentsContextType = {
  students: null,
  addStudent: () => { },
  setStudents: () => { },
};

const StudentsContext = createContext<StudentsContextType>(defaultValues);

export const useStudentsContext = () => useContext(StudentsContext);

export const StudentsContextProvider = ({ children }: { children?: React.ReactNode }) => {
  const [students, setStudents] = useState<Student[] | null>(null)

  const addStudent = (student: Student) => {
    students?.push(student)

    setStudents(students)
  }

  return (
    <StudentsContext.Provider value={{
      students,
      addStudent,
      setStudents,
    }}>{children}</StudentsContext.Provider>
  );
};
