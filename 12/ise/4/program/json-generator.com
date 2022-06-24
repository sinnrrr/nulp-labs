[
  '{{repeat(100)}}',
  {
    id: '{{index()}}',
    author: '{{firstName()}} {{surname()}}',
    name: '{{firstName()}} {{firstName()}}',
    price: '{{floating(20, 400)}}',
    pagesCount: '{{integer(100, 999)}}',
    publishedAt: '{{date()}}'
  }
]
