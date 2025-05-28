import { getVersions } from '@/components/getVersions';
import { redirect } from 'next/navigation'

export default async function RootPage() {
  const versions = await getVersions();

  if (Array.isArray(versions) && versions.length > 0) {
    // Redirect to the latest version if not already on it
    redirect(`/${versions[0].version}`);
  }

  return (
    <></>
  )
}