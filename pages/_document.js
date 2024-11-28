import { Head, Html, Main, NextScript } from "next/document";

const promo_banner = [
    "Black Friday Deals Are Live!",
    "Enjoy Up to 33% Off!",
    "Limited Time Offer Only."
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
                  [1,2].map((_, i) => (
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
                  [1, 2].map((_, i) => (
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
