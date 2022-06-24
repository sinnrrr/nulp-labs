import { CacheProvider, EmotionCache, ThemeProvider } from '@emotion/react';
import '@fontsource/roboto/300.css';
import '@fontsource/roboto/400.css';
import '@fontsource/roboto/500.css';
import '@fontsource/roboto/700.css';
import { CssBaseline } from '@mui/material';
import type { AppProps } from 'next/app';
import Head from 'next/head';
import { BooksContextProvider } from '../contexts/books';
import createEmotionCache from '../utils/createEmotionCache';
import { theme } from '../utils/theme';

// Client-side cache, shared for the whole session of the user in the browser.
const clientSideEmotionCache = createEmotionCache();

interface MyAppProps extends AppProps {
  emotionCache?: EmotionCache;
}

function MyApp({ Component, emotionCache = clientSideEmotionCache, pageProps }: MyAppProps) {
  return (
    <CacheProvider value={emotionCache}>
      <Head>
        <meta name="viewport" content="initial-scale=1, width=device-width" />
      </Head>
      <ThemeProvider theme={theme}>
        {/* CssBaseline kickstart an elegant, consistent, and simple baseline to build upon. */}
        <CssBaseline />
        <BooksContextProvider>
          <Component {...pageProps} />
        </BooksContextProvider>
      </ThemeProvider>
    </CacheProvider>
  );
}

export default MyApp
