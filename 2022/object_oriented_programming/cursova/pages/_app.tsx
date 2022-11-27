import "antd/dist/antd.css"
import type { AppProps } from "next/app"
import "../styles/Home.css"
import "../styles/global.css"
import "antd/dist/antd.less"

/*
 * Functional requirements:
 * 1) Merge sort by auto brand                                                -- new button
 * 2) Show all auto brands that have passanger cars and lorries               -- new button
 * 3) Show the most powerful passanger car and the least powerful lorry       -- new button
 * 4) Sort (DESC) by the longest path car can make, group them by type        -- [x] built in sorters
 * 5) Sort autos by the fuel consumption, group by type                       -- [x] built in sorters
 * 6) For each auto brand determine the biggest and smallest fuel consumption -- new button
 *
 * Technical requirements:
 * 1) Define default constructor (a one that does not have arguments or have a predefined values for them)
 * 2) Constructor with parameters
 * 3) Copy constructor
 */

function MyApp({ Component, pageProps }: AppProps) {
  return <Component {...pageProps} />
}

export default MyApp
