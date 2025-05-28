"use client";

import { useParams } from 'next/navigation'
import Link from 'next/link'
import { Banner } from 'nextra/components'

export default function OVBanner({ versions }) {
  const params = useParams();

  return (
    <>
      {
        (Array.isArray(versions) && params.version && params.version !== versions[0].version) ? 
          <Banner dismissible={false}>
            <Link href="/">
              You&apos;re viewing documentation for an outdated version. View the latest version: { versions[0].version } →
            </Link>
          </Banner>
        :
          null
      }
    </>
  )
}