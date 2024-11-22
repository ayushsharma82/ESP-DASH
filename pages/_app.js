import { GoogleAnalytics } from '@next/third-parties/google'
import '@/styles/globals.css'

export default function App({ Component, pageProps }) {
  return <>
    <Component {...pageProps} />
    <GoogleAnalytics gaId="G-H1X62VMQNV" />
  </>
}