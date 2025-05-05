import nextra from 'nextra';

const withNextra = nextra({
  // Nextra 4 options
});

const nextOptions = {
  output: 'export',
  images: {
    unoptimized: true,
  },
};

export default withNextra(nextOptions);

// If you have other Next.js configurations, you can pass them as the parameter:
// export default withNextra({ /* other next.js config */ })
