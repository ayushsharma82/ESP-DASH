import fs from 'fs';
import path from 'path';
import { importPage } from 'nextra/pages'
import { Search } from 'nextra/components'
import { useMDXComponents as getMDXComponents } from '@/mdx-components'
import { Layout, Navbar } from 'nextra-theme-docs'
import { getPageMap } from 'nextra/page-map'
import { Logo } from '@/components/Logo'
import OldVersionBanner from '@/components/OldVersionBanner';

export async function generateStaticParams() {
  const contentDir = path.join(process.cwd(), 'content');
  const versions = fs.readdirSync(contentDir).filter((name) =>
    fs.statSync(path.join(contentDir, name)).isDirectory()
  );

  const params = [];

  for (const version of versions) {
    const versionDir = path.join(contentDir, version);

    function walk(dir, mdxPath = []) {
      const entries = fs.readdirSync(dir, { withFileTypes: true });
      for (const entry of entries) {
        if (entry.isDirectory()) {
          walk(path.join(dir, entry.name), [...mdxPath, entry.name]);
        } else if (entry.isFile() && entry.name.endsWith('.mdx')) {
          const name = entry.name.replace(/\.mdx$/, '');
          // Use [] for index, otherwise array of segments
          const paramPath = [...mdxPath, name].filter(Boolean);
          params.push({
            version,
            mdxPath: paramPath.length === 1 && paramPath[0] === 'index' ? [''] : paramPath,
          });
        }
      }
    }

    walk(versionDir, []);
  }

  return params;
}

// Fix: Destructure version and mdxPath from params in generateMetadata
export async function generateMetadata({ params }) {
  const { version, mdxPath } = await params;
  const pagePath = mdxPath?.length ? [version, ...mdxPath] : [version];
  const { metadata } = await importPage(pagePath);
  return metadata;
}

const Wrapper = getMDXComponents().wrapper

export default async function Page(props) {
  const { version, mdxPath } = await props.params;
  const pagePath = mdxPath?.length ? [version, ...mdxPath] : [version];
  const result = await importPage(pagePath);
  const { default: MDXContent, toc, metadata } = result;

  // Use getPageMap with route argument to avoid undefined/null
  let filteredPageMap;
  try {
    filteredPageMap = await getPageMap('/' + version);
    if (!Array.isArray(filteredPageMap)) filteredPageMap = [];
  } catch {
    filteredPageMap = [];
  }

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

  return (
    <Layout
      darkMode={true}
      // banner={<Banner storageKey="Nextra 2">Nextra 2 Alpha</Banner>}
      navbar={navbar}
      footer={
        <div className="flex flex-col items-center text-xs py-4 px-4 text-zinc-500 border-t border-zinc-200 dark:border-zinc-900 bg-zinc-100 dark:bg-zinc-950">
          <div>Copyright © { new Date().getFullYear() } <a href="https://softt.io" className='hover:text-blue-500 transition-colors' target="_blank">Softt</a>. All rights reserved.</div>
        </div>
      }
      search={
        <Search searchOptions={{
          filters: {
            version: version,
          }
        }} />
      }
      editLink="Edit this page on GitHub"
      docsRepositoryBase="https://github.com/ayushsharma82/ESP-DASH/tree/docs"
      sidebar={{ defaultMenuCollapseLevel: 2 }}
      pageMap={filteredPageMap}
    >
      <OldVersionBanner />
      <Wrapper toc={toc} metadata={metadata}>
        <span className='hidden' data-pagefind-filter="version">{version}</span>
        <MDXContent {...props} params={props.params} />
      </Wrapper>
    </Layout>
  );
}