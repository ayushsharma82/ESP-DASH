import { Layout, Navbar } from 'nextra-theme-docs';
import { Logo } from '@/components/Logo';
import Link from 'next/link';
import { getPageMap } from 'nextra/page-map';

export default async function NotFound() {
  const navbar = (
    <Navbar
      logo={<Logo />}
      projectLink="https://github.com/ayushsharma82/ESP-DASH"
    >
      <a href="https://espdash.pro" target="_blank" className="text-zinc-900 bg-white hover:bg-zinc-100 border border-zinc-200 focus:ring-4 focus:outline-hidden focus:ring-zinc-100 font-medium rounded-lg text-sm px-5 py-2 text-center inline-flex items-center dark:focus:ring-zinc-600 dark:bg-zinc-800 dark:border-zinc-700 dark:text-white dark:hover:bg-zinc-700">
        <span className='hidden sm:block me-1'>
          Upgrade to
        </span>
        <img src="/img/pro-badge.gif" alt="" width={38} />
        <svg xmlns="http://www.w3.org/2000/svg" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="ms-2"><path d="M5 12h14" /><path d="m12 5 7 7-7 7" /></svg>
      </a>
    </Navbar>
  );

  let pageMap = [];
  try {
    pageMap = await getPageMap('/');
    if (!Array.isArray(pageMap)) pageMap = [];
  } catch {
    pageMap = [];
  }

  return (
    <Layout
      darkMode={true}
      navbar={navbar}
      footer={
        <div className="flex flex-col items-center text-xs py-4 px-4 text-zinc-500 border-t border-zinc-200 dark:border-zinc-900 bg-zinc-100 dark:bg-zinc-950">
          <div>Copyright © { new Date().getFullYear() } <a href="https://softt.io" className='hover:text-blue-500 transition-colors' target="_blank">Softt</a>. All rights reserved.</div>
        </div>
      }
      editLink="Edit this page on GitHub"
      docsRepositoryBase="https://github.com/ayushsharma82/ESP-DASH/tree/docs"
      pageMap={pageMap}
    >
      <div className="flex flex-col items-center justify-center min-h-[60vh] text-center">
        <h1 className="text-4xl font-bold mb-4">404 - Page Not Found</h1>
        <p className="mb-6 text-zinc-500">Sorry, the page you are looking for does not exist or has been moved to a new URL.</p>
        <Link href="/" className="text-white bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:ring-blue-300 font-medium rounded-lg text-sm px-5 py-2.5 me-2 mb-2 dark:bg-blue-600 dark:hover:bg-blue-700 focus:outline-none dark:focus:ring-blue-800">Go to Latest Docs</Link>
      </div>
    </Layout>
  );
}
