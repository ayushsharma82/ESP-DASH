import HomepageFeatures from '@site/src/components/HomepageFeatures';
import Layout from '@theme/Layout';
import Link from '@docusaurus/Link';
import React from 'react';
import clsx from 'clsx';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';

import styles from './index.module.css';

function HomepageHeader() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <header className={clsx('hero hero--secondary', styles.heroBanner)}>
      <div className="container">
        <br/>
        <br/>
        <img src="/img/dash-splash.png" width={280} />
        <br/>
        <br/>
        <p className="hero__subtitle">{siteConfig.tagline}</p>
        <div className={styles.buttons} style={{ gap: 15 }}>
          <Link
            className="button button--primary button--lg"
            style={{ background: '#72c766', borderColor: '#72c766', fontWeight: 500 }}
            to="/docs/intro">
            Docs
          </Link>
          <Link
            className="button button--lg"
            style={{ background: '#3b3c51', borderColor: '#72c766', fontWeight: 500 }}
            to="/docs/intro">
            Upgrade to Pro
          </Link>
        </div>
        <br/>
      </div>
    </header>
  );
}

export default function Home() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <Layout
      title={`Blazing Fast Dashboard For ESP32 & ESP8266`}
      description="Description will go into a meta tag in <head />">
      <HomepageHeader />
      <main>
        <HomepageFeatures />
      </main>
    </Layout>
  );
}
