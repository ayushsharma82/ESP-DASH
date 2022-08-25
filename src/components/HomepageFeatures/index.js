import React from 'react';
import clsx from 'clsx';

import styles from './styles.module.css';

const FeatureList = [
  {
    title: 'Easy to Use',
    Svg: require('@site/static/img/dash-docs-flash.svg').default,
    description: (
      <>
        DASH was designed to automate dashboard creation part from the gound up. Hence, the library provides you with easy-to-access C++ components to make a complete dashboard.
      </>
    ),
  },
  {
    title: 'Focus on What Matters',
    Svg: require('@site/static/img/dash-docs-focus.svg').default,
    description: (
      <>
        Don't know HTML/CSS/JS? Then DASH is what you need! Focus on making your project awesome instead of spending time in building webpages.
      </>
    ),
  },
  {
    title: 'Realtime Updates',
    Svg: require('@site/static/img/dash-docs-realtime.svg').default,
    description: (
      <>
        The backbone of DASH is WebSocket protocol which allows you send updates to every open dashboard with the latest value. All open dashboards will be synced with eachother automatically.
      </>
    ),
  },
];

function Feature({Svg, title, description}) {
  return (
    <div className={clsx('col col--4')}>
      <div className="text--center">
        <Svg className={styles.featureSvg} role="img" />
      </div>
      <div className="text--center padding-horiz--md">
        <h3>{title}</h3>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className="container">
        <br/>
        <br/>
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
        <br/>
        <br/>
      </div>
    </section>
  );
}
