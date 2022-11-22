import { PageHeader } from "antd"
import type { NextPage } from "next"
import Head from "next/head"
import { useEffect } from "react"
import { CarsTable } from "../components/CarsTable"

const Home: NextPage = () => {
  useEffect(() => {
    // prompt before closing the tab
    window.onbeforeunload = () => ""
  }, [])

  return (
    <div className="site-page-header-ghost-wrapper">
      <Head>
        <title>Cars Manager</title>
        <meta name="description" content="Your personal car info manager" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <PageHeader ghost={false} title="Cars Manager">
        <main>
          <CarsTable />
        </main>
      </PageHeader>
    </div>
  )
}

export default Home
