import { Button } from "@mui/material";
import { ChangeEventHandler, FunctionComponent } from "react";

type LoadDataFileButtonProps = {
  children?: React.ReactNode,
  onSubmit?: (content: string) => void,
  onError?: (error: Error) => void
}

export const LoadDataFileButton: FunctionComponent<LoadDataFileButtonProps> = (props) => {
  const onChange: ChangeEventHandler<HTMLInputElement> = (e) => {
    const file = e.target.files?.item(0)
    const reader = new FileReader()

    if (!file) {
      props.onError && props.onError(new Error("No files provided!"))
      return;
    }

    reader.readAsText(file)

    reader.onload = (event) => {
      props.onSubmit && props.onSubmit(event.target?.result as string)
    }

    reader.onerror = (error) => {
      props.onError && props.onError(error.target?.error!)
    }
  }

  return (
    <Button
      variant="contained"
      component="label"
      sx={{ zIndex: 1 }}
    >
      {props.children}

      <input
        type="file"
        accept='application/json'
        onChange={onChange}
        hidden
      />
    </Button>
  )
}
