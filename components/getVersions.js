import fs from 'fs';
import path from 'path';
import semver from 'semver';

const normalizeVersion = (v) => v.replace(/x/g, '0');

export async function getVersions() {
  const contentPath = path.join(process.cwd(), 'content');
  const entries = fs.readdirSync(contentPath, { withFileTypes: true });

  return (
    entries
      .filter((entry) => entry.isDirectory())
      .map((entry) => {
        return {
          version: entry.name,
          normalized: normalizeVersion(entry.name),
        };
      })
      // sort using semver
      .sort((a, b) => {
        const aVersion = semver.parse(a.normalized);
        const bVersion = semver.parse(b.normalized);
        return semver.compare(bVersion, aVersion); // Sort descending
      })
  );
}
