"use client";

import { useParams } from 'next/navigation'
import Link from 'next/link'
import { Banner } from 'nextra/components'
import { ExclamationTriangleIcon } from '@heroicons/react/20/solid';

export default function OVBanner({ versions }) {
  const params = useParams();

  return (
    <>
      {
        (Array.isArray(versions) && params.version && params.version !== versions[0].version) ? 
          <Link href="/" className='min-h-10 px-4 py-2 text-center w-full bg-zinc-900/60 dark:bg-zinc-600/40 text-white flex items-center justify-center z-50'>
            <ExclamationTriangleIcon className='w-5 h-5 mr-2 text-yellow-500' />
            <span className='text-sm'>
              You&apos;re viewing documentation of an outdated version. 
              Check the latest documentation for {versions[0].version} →
            </span>
          </Link>
        :
          null
      }
    </>
  )
}