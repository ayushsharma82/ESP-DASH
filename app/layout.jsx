/* eslint-env node */
import '@/styles/globals.css';
import localFont from 'next/font/local'
import { Layout, Navbar } from 'nextra-theme-docs'
import { Banner, Head } from 'nextra/components'
import { getPageMap } from 'nextra/page-map'
import 'nextra-theme-docs/style.css'
import OldVersionBanner from '@/components/OldVersionBanner';

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
        { children }
      </body>
    </html>
  )
}