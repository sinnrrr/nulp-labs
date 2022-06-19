export const intersection = (arr1: number[], arr2: number[]) =>
  arr1.some((v) => arr2.includes(v))
