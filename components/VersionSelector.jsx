import Selector from "./Selector";
import { getVersions } from "./getVersions";

export default async function VersionSelector() {
  const versions = await getVersions();

  return (
    <Selector versions={versions} />
  )
}