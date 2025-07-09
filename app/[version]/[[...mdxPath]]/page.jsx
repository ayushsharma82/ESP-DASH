import fs from 'fs';
import path from 'path';
import { importPage } from 'nextra/pages'
import { useMDXComponents as getMDXComponents } from '@/mdx-components'

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

  return (
    <Wrapper toc={toc} metadata={metadata}>
      <span className='hidden' data-pagefind-filter="version">{version}</span>
      <MDXContent {...props} params={props.params} />
    </Wrapper>
  );
}