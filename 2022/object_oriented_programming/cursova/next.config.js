/** @type {import('next').NextConfig} */
// next.config.js

const withLess = require("next-with-less")
/** @type {import('next').NextConfig} */
module.exports = withLess({
  lessLoaderOptions: {
    lessOptions: {
      modifyVars: {
        // Add variables here
        "font-family": "Quicksand, sans-serif",
        "primary-color": "#6610f2",
      },
    },
  },
  compiler: {
    styledComponents: true,
  },
})
