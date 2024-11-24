import { Head, Html, Main, NextScript } from "next/document";

const promo_banner = [
  "Black Friday 2024 Sale is Live!",
  "Flat 33% off on Advantage Bundle",
  "Upgrade Now at Lowest Price Ever!"
];

export default function Document() {
  return (
    <Html lang="en">
      <Head />
      <body className="antialiased">
      {
          promo_banner && (
            <div className="relative flex overflow-x-hidden text-zinc-200 font-semibold text-sm uppercase bg-indigo-600">
              <div className="py-2 animate-marquee whitespace-nowrap">
                {
                  [1,2,3].map((_, i) => (
                    <span key={'pb-'+i} className='mx-6'>
                      {
                        promo_banner.map((item, i) => (
                          <span className="mx-4" key={'pbs-'+i}>{item}</span>
                        ))
                      }
                    </span>
                  ))
                }
              </div>

              <div className="absolute top-0 py-2 animate-marquee2 whitespace-nowrap">
                {
                  [1, 2, 3].map((_, i) => (
                    <span key={'pba-' + i} className='mx-6'>
                      {
                        promo_banner.map((item, i) => (
                          <span className="mx-4" key={'pbas-' + i}>{item}</span>
                        ))
                      }
                    </span>
                  ))
                }
              </div>
            </div>
          )
        }
        <Main />
        <NextScript />
      </body>
    </Html>
  );
}
