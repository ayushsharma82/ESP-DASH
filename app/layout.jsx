/* eslint-env node */
import '@/styles/globals.css';
import localFont from 'next/font/local'
import { Layout, Navbar } from 'nextra-theme-docs'
import { Banner, Head } from 'nextra/components'
import { getPageMap } from 'nextra/page-map'
import 'nextra-theme-docs/style.css'

import { Logo } from '@/components/Logo'

const geistFont = localFont({
  src: '../styles/Geist-Regular.woff',
  display: 'swap',
  variable: '--font-geist',
});

const geistMonoFont = localFont({
  src: '../styles/GeistMono-Regular.woff',
  display: 'swap',
  variable: '--font-geist-mono',
})

export const metadata = {
  metadataBase: new URL('https://docs.espdash.pro'),
  title: {
    template: '%s - ESP-DASH Docs'
  },
  description: 'ESP-DASH Docs: Learn more about ESP-DASH',
  applicationName: 'ESP-DASH Docs',
  generator: 'Next.js',
  appleWebApp: {
    title: 'ESP-DASH Docs'
  },
}

export default async function RootLayout({ children }) {
  const navbar = (
    <Navbar
      logo={<Logo />}
      projectLink='https://github.com/ayushsharma82/ESP-DASH'
    >
      <a href="https://espdash.pro" target='_blank' className="text-zinc-900 bg-white hover:bg-zinc-100 border border-zinc-200 focus:ring-4 focus:outline-hidden focus:ring-zinc-100 font-medium rounded-lg text-sm px-5 py-2 text-center inline-flex items-center dark:focus:ring-zinc-600 dark:bg-zinc-800 dark:border-zinc-700 dark:text-white dark:hover:bg-zinc-700">
        <span className='hidden sm:block me-1'>
          Upgrade to
        </span>
        {/* eslint-disable-next-line @next/next/no-img-element */}
        <img src="/img/pro-badge.gif" alt="" width={38} />
        <svg xmlns="http://www.w3.org/2000/svg" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="ms-2"><path d="M5 12h14" /><path d="m12 5 7 7-7 7" /></svg>
      </a>
    </Navbar>
  )
  const pageMap = await getPageMap()
  return (
    <html lang="en" dir="ltr" suppressHydrationWarning>
      <Head
        faviconGlyph="✦"
        color={{
          hue: {
            dark: 160,
            light: 160
          },
          saturation: {
            dark: 87,
            light: 47
          },
          lightness: {
            dark: 44,
            light: 44
          }
        }}  
      >
        <link rel="shortcut icon" href="/favicon.ico" />
      </Head>
      <body className={`${geistFont.variable} ${geistMonoFont.variable} font-sans`}>
        <Layout
          darkMode={true}
          // banner={<Banner storageKey="Nextra 2">Nextra 2 Alpha</Banner>}
          navbar={navbar}
          footer={
            <div className="flex flex-col items-center text-xs py-4 px-4 text-zinc-500 border-t border-zinc-200 dark:border-zinc-900 bg-zinc-100 dark:bg-zinc-950">
              <div>Copyright © { new Date().getFullYear() } <a href="https://softt.io" className='hover:text-blue-500 transition-colors' target="_blank">Softt</a>. All rights reserved.</div>
            </div>
          }
          editLink="Edit this page on GitHub"
          docsRepositoryBase="https://github.com/ayushsharma82/ESP-DASH/tree/docs"
          sidebar={{ defaultMenuCollapseLevel: 2 }}
          pageMap={pageMap}
        >
          {children}
        </Layout>
      </body>
    </html>
  )
}