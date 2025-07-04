'use client'

import { useCallback, useState } from 'react'
import { Label, Listbox, ListboxButton, ListboxOption, ListboxOptions } from '@headlessui/react'
import { ChevronUpDownIcon } from '@heroicons/react/16/solid'
import { CheckIcon } from '@heroicons/react/20/solid'
import { useRouter } from 'next/navigation'
import { useParams } from 'next/navigation'

export default function Selector({ versions }) {
  const params = useParams();
  const router = useRouter();
  const [selected, setSelected] = useState(params.version);

  const onChangeHandler = useCallback((value) => {
    setSelected(value)
    // Redirect to new version path
    router.push(`/${value}`)
  }, [router, setSelected])

  return (
    <Listbox value={selected} onChange={onChangeHandler}>
      <Label className="block text-sm/6 font-medium text-zinc-900 dark:text-zinc-400">Select Version</Label>
      <div className="relative mt-2">
        <ListboxButton className="grid w-full cursor-default grid-cols-1 rounded-md bg-transparent dark:bg-zinc-900 py-1.5 pr-2 pl-3 text-left text-zinc-900 dark:text-zinc-300 outline-1 -outline-offset-1 outline-zinc-300 dark:outline-zinc-800 focus:outline-2 focus:-outline-offset-2 focus:outline-indigo-600 font-normal sm:text-sm/6">
          <span className="col-start-1 row-start-1 truncate pr-6">{selected}</span>
          <ChevronUpDownIcon
            aria-hidden="true"
            className="col-start-1 row-start-1 size-5 self-center justify-self-end text-gray-500 sm:size-4"
          />
        </ListboxButton>

        <ListboxOptions
          transition
          className="absolute z-10 mt-1 max-h-60 w-full overflow-auto rounded-md bg-white dark:bg-zinc-900 py-1 text-base shadow-lg ring-1 ring-black/5 dark:ring-zinc-800 focus:outline-hidden data-leave:transition data-leave:duration-100 data-leave:ease-in data-closed:data-leave:opacity-0 sm:text-sm"
        >
          {Array.isArray(versions) && versions.map((val, index) => (
            <ListboxOption
              key={'v-'+index}
              value={val.version}
              className="group relative cursor-default py-1.5 pr-9 pl-3 text-gray-900 dark:text-zinc-300 select-none data-focus:bg-indigo-600 data-focus:text-white data-focus:outline-hidden"
            >
              <span className="block truncate font-normal group-data-selected:font-semibold">
                {val.version}
                {
                  index === 0 ? 
                    <span className="text-sm tracking-wide text-zinc-500 dark:text-indigo-400 ms-2">(latest)</span>
                  : null
                }
              </span>

              <span className="absolute inset-y-0 right-0 flex items-center pr-4 text-indigo-400 group-not-data-selected:hidden group-data-focus:text-white">
                <CheckIcon aria-hidden="true" className="size-5" />
              </span>
            </ListboxOption>
          ))}
        </ListboxOptions>
      </div>
    </Listbox>
  )
}
