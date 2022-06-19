import {
  createContext, useContext, useState
} from "react";
import { Student } from "../schemas/student";

type StudentsContextType = {
  students: Student[] | null,
  studentsDataString: string | null,
  addStudent: (student: Student) => void,
  setStudents: (students: Student[]) => void,
};

const defaultValues: StudentsContextType = {
  students: null,
  studentsDataString: null,
  addStudent: () => { },
  setStudents: () => { },
};

const StudentsContext = createContext<StudentsContextType>(defaultValues);

export const useStudentsContext = () => useContext(StudentsContext);

export const StudentsContextProvider = ({ children }: { children?: React.ReactNode }) => {
  const [students, setStudents] = useState<Student[] | null>(null)

  const addStudent = (student: Student) => {
    setStudents([...students || [], student])
  }

  return (
    <StudentsContext.Provider value={{
      students,
      studentsDataString: "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(students)),
      addStudent,
      setStudents,
    }}>{children}</StudentsContext.Provider>
  );
};
