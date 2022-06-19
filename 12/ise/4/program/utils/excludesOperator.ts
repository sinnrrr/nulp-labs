import { GridCellParams, GridColDef, GridFilterInputMultipleValue, GridFilterItem, GridFilterOperator } from "@mui/x-data-grid";
import { intersection } from "./intersection";

export const excludesOperator: GridFilterOperator = {
  label: 'excludes',
  value: 'excludes',
  getApplyFilterFn: (filterItem: GridFilterItem, _column: GridColDef) => {
    if (!filterItem.columnField || !filterItem.value || !filterItem.operatorValue) {
      return null;
    }

    return (params: GridCellParams): boolean => {
      return !intersection(params.value, filterItem.value.flat());
    };
  },
  InputComponent: GridFilterInputMultipleValue,
  InputComponentProps: { type: 'number' },
};
