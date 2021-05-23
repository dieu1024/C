// Create by jiwoo

import java.net.*;
import java.util.*;

import javax.net.ssl.*;
import java.security.*;
import java.security.cert.*;

import java.io.*;


public class Crawler {

	public static void main(String[] args) throws MalformedURLException {
		int depth = 0;
		if (args.length != 2) {
			System.out.println("You must write in the form of [java Crawler <URL> <depth>]");
			System.exit(1);
		}
		
		else {
				depth = Integer.parseInt(args[1]);
		}
	
		LinkedList<UrlDepthPair> pendingUrls = new LinkedList<UrlDepthPair>();
		LinkedList<UrlDepthPair> processedUrls = new LinkedList<UrlDepthPair>();
		
		UrlDepthPair currentDepthPair = new UrlDepthPair(args[0],0);
		
		pendingUrls.add(currentDepthPair);
		
		ArrayList<String> seenUrls = new ArrayList<String>();
		seenUrls.add(currentDepthPair.toString());
		
		while (!pendingUrls.isEmpty()) {
			UrlDepthPair nextURLPair = pendingUrls.remove(0);
			processedUrls.add(nextURLPair);
			int curDepth = nextURLPair.getDepth();
			
			try {
				TrustManager[] trustAllCerts = new TrustManager[] {new X509TrustManager() {
					public X509Certificate[] getAcceptedIssuers() {return null;}
					public void checkClientTrusted(X509Certificate[] certs, String authType) {}
					public void checkServerTrusted(X509Certificate[] certs, String authType) {}
				}};
				SSLContext sc = SSLContext.getInstance("SSL");
				sc.init(null, trustAllCerts, new SecureRandom());
				HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
			} catch (Exception e) {System.exit(1);}
			
			try {
				URL url = new URL(nextURLPair.getURLString());
				HttpURLConnection conn = (HttpURLConnection)url.openConnection();
				conn.setConnectTimeout(10000);
				conn.setReadTimeout(3000);
				BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
				
				for (String line; (line = in.readLine()) != null; ) {
					if (curDepth < depth) {
						int cursor = 0;
						int ecursor = 0;
						while (true) {
							String word = "<a href=\"";
							cursor = line.indexOf("<a href=\"http", cursor);
							if (cursor < 0) break;
							cursor += word.length();
							ecursor = line.indexOf("\"",cursor);
							String nurl = line.substring(cursor,ecursor);
							if (seenUrls.contains(nurl)) continue;
							else {
								pendingUrls.add(new UrlDepthPair (nurl, curDepth + 1));
								seenUrls.add(nurl);
							}
						}
					}
				}
				conn.disconnect();
				in.close();
			} catch (Exception e) { 
				continue;
				}
		}
		for (UrlDepthPair i : processedUrls) {
			System.out.println(i);
		}
		System.out.println("Found " + processedUrls.size() + " pages starting from " + args[0]);
	}

}
