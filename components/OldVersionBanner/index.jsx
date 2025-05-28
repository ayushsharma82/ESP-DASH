import { getVersions } from "../getVersions";
import OVBanner from "./banner";


export default async function OldVersionBanner() {
  const versions = await getVersions();
  return (
    <OVBanner versions={versions} />
  )
}