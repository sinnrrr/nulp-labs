[
  '{{repeat(100)}}',
  {
    id: '{{index()}}',
    firstName: '{{firstName()}}',
    lastName: '{{surname()}}',
    birthDate: '{{date()}}',
    grades: [
      '{{repeat(6)}}',
      '{{integer(1, 5)}}'
    ],
  }
]
