# Interview Mate — Website Version

A responsive, offline-friendly mock interview practice website.

## Run it
1. Extract the ZIP file.
2. Open the `Interview_Mate_Website` folder.
3. Double-click `index.html` to open it in Chrome or Edge.
4. Choose an interview track and begin practising.

You can also open the folder in VS Code and use any local preview extension.

## Included
- C++ Developer, General Fresher, and Python Developer tracks
- 10 questions per session
- Chat-style interview interface and progress bar
- Rule-based keyword scoring, feedback, and answer tips
- Session history stored in this browser using localStorage
- Downloadable text report
- Responsive layout for desktop and mobile

## Important note about the technology
The original `cpp_console_version/main.cpp` is included to retain the C++ console project. The browser website uses HTML, CSS, and JavaScript because browsers do not execute a normal C++ console program directly. The website's interview flow is a local, rule-based demo; it does not connect to an AI service or send answers to a server.

## Files
- `index.html` — website structure
- `style.css` — responsive visual design
- `script.js` — interview questions, flow, scoring, history, and report download
- `cpp_console_version/main.cpp` — C++ console implementation from the companion project
