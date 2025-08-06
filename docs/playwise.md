---
Header:
  Left: ""
  Center: ""
  Right: ""
---

**PlayWise Hackathon -- Solution Document**

**Track:** DSA -- Smart Playlist Management System

**1. Student Information**

| Field               | Details |
|---------------------|---------|
| Full Name           | Gundam Himavarshith Reddy |
| Registration Number | RA2211026010170 |
| Department / Branch | CINTEL / CSE AI&ML |
| Year                | 4th |
| Email ID            | hg5605@srmist.edu.in |

**2. Problem Scope and Track Details**

| Section                  | Details                            |
|--------------------------|------------------------------------|
| Hackathon Track          | DSA -- PlayWise Playlist Engine    |
|  Core Modules Implemented| ✅ Playlist Engine (Linked List)    |
|                          | ✅ Playback History (Stack)         |
|                          | ✅ Song Rating Tree (BST)           |
|                          | ✅ Instant Song Lookup (HashMap)    |
|                          | ✅ Time-based Sorting               |
|                          | ✅ Space-Time Playback Optimization |
|                          | ✅ System Snapshot Module           |

**Additional Use Cases Implemented**

- Scenario 1: **Auto-Sorting Favorite Songs Queue** - Priority queue that automatically maintains songs sorted by listening duration and play count, providing personalized recommendations based on user behavior patterns and listening history.

- Scenario 2: **Duplicate Song Detection and Removal** - HashSet-based system to identify and clean duplicate songs based on composite keys (title + artist), ensuring data integrity and preventing redundant entries in playlists.

- Scenario 3: **Real-time System Dashboard** - Live monitoring and analytics system providing comprehensive performance metrics, user activity statistics, and system health indicators with real-time updates.

**3. Architecture & Design Overview**

- **System Architecture Diagram**  
  <div align="center">
   <svg aria-roledescription="flowchart-v2" role="graphics-document document" viewBox="-8 -8 980.0067138671875 578.8571166992188" style="max-width: 980.0067138671875px;" xmlns="http://www.w3.org/2000/svg" width="100%" id="mermaid-svg-1754428303498-dbo0r2fa9"><style>#mermaid-svg-1754428303498-dbo0r2fa9{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:14px;fill:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .error-icon{fill:#5a1d1d;}#mermaid-svg-1754428303498-dbo0r2fa9 .error-text{fill:#f97583;stroke:#f97583;}#mermaid-svg-1754428303498-dbo0r2fa9 .edge-thickness-normal{stroke-width:2px;}#mermaid-svg-1754428303498-dbo0r2fa9 .edge-thickness-thick{stroke-width:3.5px;}#mermaid-svg-1754428303498-dbo0r2fa9 .edge-pattern-solid{stroke-dasharray:0;}#mermaid-svg-1754428303498-dbo0r2fa9 .edge-pattern-dashed{stroke-dasharray:3;}#mermaid-svg-1754428303498-dbo0r2fa9 .edge-pattern-dotted{stroke-dasharray:2;}#mermaid-svg-1754428303498-dbo0r2fa9 .marker{fill:#333;stroke:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .marker.cross{stroke:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 svg{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:14px;}#mermaid-svg-1754428303498-dbo0r2fa9 .label{font-family:"trebuchet ms",verdana,arial,sans-serif;color:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .cluster-label text{fill:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .cluster-label span,#mermaid-svg-1754428303498-dbo0r2fa9 p{color:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .label text,#mermaid-svg-1754428303498-dbo0r2fa9 span,#mermaid-svg-1754428303498-dbo0r2fa9 p{fill:#333;color:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .node rect,#mermaid-svg-1754428303498-dbo0r2fa9 .node circle,#mermaid-svg-1754428303498-dbo0r2fa9 .node ellipse,#mermaid-svg-1754428303498-dbo0r2fa9 .node polygon,#mermaid-svg-1754428303498-dbo0r2fa9 .node path{fill:#ffffff;stroke:#333;stroke-width:1px;}#mermaid-svg-1754428303498-dbo0r2fa9 .flowchart-label text{text-anchor:middle;}#mermaid-svg-1754428303498-dbo0r2fa9 .node .label{text-align:center;}#mermaid-svg-1754428303498-dbo0r2fa9 .node.clickable{cursor:pointer;}#mermaid-svg-1754428303498-dbo0r2fa9 .arrowheadPath{fill:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .edgePath .path{stroke:#333;stroke-width:2.0px;}#mermaid-svg-1754428303498-dbo0r2fa9 .flowchart-link{stroke:#333;fill:none;}#mermaid-svg-1754428303498-dbo0r2fa9 .edgeLabel{background-color:#ffffff;text-align:center;}#mermaid-svg-1754428303498-dbo0r2fa9 .edgeLabel rect{opacity:0.9;background-color:#ffffff;fill:#ffffff;}#mermaid-svg-1754428303498-dbo0r2fa9 .labelBkg{background-color:rgba(255, 255, 255, 0.9);}#mermaid-svg-1754428303498-dbo0r2fa9 .cluster rect{fill:rgba(240, 240, 240, 0.8);stroke:#333;stroke-width:1px;}#mermaid-svg-1754428303498-dbo0r2fa9 .cluster text{fill:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 .cluster span,#mermaid-svg-1754428303498-dbo0r2fa9 p{color:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:12px;background:#ffffff;border:1px solid #333;border-radius:2px;pointer-events:none;z-index:100;}#mermaid-svg-1754428303498-dbo0r2fa9 .flowchartTitleText{text-anchor:middle;font-size:18px;fill:#333;}#mermaid-svg-1754428303498-dbo0r2fa9 :root{--mermaid-font-family:"trebuchet ms",verdana,arial,sans-serif;}#mermaid-svg-1754428303498-dbo0r2fa9 .coreClass&gt;*{fill:#e1f5fe!important;stroke:#01579b!important;stroke-width:2px!important;}#mermaid-svg-1754428303498-dbo0r2fa9 .coreClass span{fill:#01579b!important;stroke:none!important;}#mermaid-svg-1754428303498-dbo0r2fa9 .featureClass&gt;*{fill:#f3e5f5!important;stroke:#4a148c!important;stroke-width:2px!important;}#mermaid-svg-1754428303498-dbo0r2fa9 .featureClass span{fill:#4a148c!important;stroke:none!important;}#mermaid-svg-1754428303498-dbo0r2fa9 .uiClass&gt;*{fill:#e8f5e8!important;stroke:#1b5e20!important;stroke-width:2px!important;}#mermaid-svg-1754428303498-dbo0r2fa9 .uiClass span{fill:#1b5e20!important;stroke:none!important;}#mermaid-svg-1754428303498-dbo0r2fa9 foreignObject div{font-size:12px!important;line-height:1.2!important;}</style><g><marker orient="auto" markerHeight="12" markerWidth="12" markerUnits="userSpaceOnUse" refY="5" refX="6" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd"><path style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 0 0 L 10 5 L 0 10 z"/></marker><marker orient="auto" markerHeight="12" markerWidth="12" markerUnits="userSpaceOnUse" refY="5" refX="4.5" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointStart"><path style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 0 5 L 10 10 L 10 0 z"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5" refX="11" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303498-dbo0r2fa9_flowchart-circleEnd"><circle style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" r="5" cy="5" cx="5"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5" refX="-1" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303498-dbo0r2fa9_flowchart-circleStart"><circle style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" r="5" cy="5" cx="5"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5.2" refX="12" viewBox="0 0 11 11" class="marker cross flowchart" id="mermaid-svg-1754428303498-dbo0r2fa9_flowchart-crossEnd"><path style="stroke-width: 2; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 1,1 l 9,9 M 10,1 l -9,9"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5.2" refX="-1" viewBox="0 0 11 11" class="marker cross flowchart" id="mermaid-svg-1754428303498-dbo0r2fa9_flowchart-crossStart"><path style="stroke-width: 2; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 1,1 l 9,9 M 10,1 l -9,9"/></marker><g class="root"><g class="clusters"/><g class="edgePaths"><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-UI LE-APP" id="L-UI-APP-0" d="M509.819,52.143L509.819,56.31C509.819,60.476,509.819,68.81,509.819,76.26C509.819,83.71,509.819,90.276,509.819,93.56L509.819,96.843"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-SONG" id="L-APP-SONG-0" d="M447.162,136.56L393.703,143.681C340.244,150.802,233.325,165.044,179.866,180.677C126.406,196.31,126.406,213.333,126.406,230.357C126.406,247.381,126.406,264.405,126.406,281.429C126.406,298.452,126.406,315.476,126.406,332.5C126.406,349.524,126.406,366.548,126.406,383.571C126.406,400.595,126.406,417.619,126.406,434.643C126.406,451.667,126.406,468.69,181.509,484.542C236.611,500.394,346.816,515.073,401.918,522.413L457.02,529.753"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-PL" id="L-APP-PL-0" d="M447.162,138.232L404.366,145.074C361.57,151.916,275.977,165.601,233.181,180.955C190.385,196.31,190.385,213.333,190.385,230.357C190.385,247.381,190.385,264.405,193.397,276.414C196.408,288.423,202.431,295.418,205.443,298.915L208.455,302.412"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-HIST" id="L-APP-HIST-0" d="M514.924,154.286L515.739,158.452C516.555,162.619,518.187,170.952,519.003,183.631C519.819,196.31,519.819,213.333,519.819,230.357C519.819,247.381,519.819,264.405,525.052,276.823C530.286,289.242,540.754,297.055,545.988,300.961L551.221,304.868"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-RT" id="L-APP-RT-0" d="M447.162,147.383L429.782,152.7C412.401,158.017,377.64,168.651,360.26,182.48C342.879,196.31,342.879,213.333,342.879,230.357C342.879,247.381,342.879,264.405,349.336,276.642C355.792,288.879,368.705,296.329,375.162,300.055L381.618,303.78"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-DB" id="L-APP-DB-0" d="M572.475,144.372L595.039,150.191C617.602,156.01,662.73,167.648,685.293,181.979C707.857,196.31,707.857,213.333,707.857,230.357C707.857,247.381,707.857,264.405,711.253,276.447C714.648,288.489,721.439,295.549,724.834,299.079L728.23,302.609"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-SORT" id="L-APP-SORT-0" d="M447.162,135.109L380.253,142.472C313.343,149.835,179.523,164.56,112.613,175.206C45.703,185.852,45.703,192.419,45.703,195.702L45.703,198.986"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-DASH" id="L-APP-DASH-0" d="M570.207,154.286L579.858,158.452C589.509,162.619,608.812,170.952,618.463,178.402C628.114,185.852,628.114,192.419,628.114,195.702L628.114,198.986"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-CLEAN" id="L-APP-CLEAN-0" d="M572.475,139.363L609.871,146.016C647.267,152.67,722.06,165.978,759.456,175.915C796.853,185.852,796.853,192.419,796.853,195.702L796.853,198.986"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-APP LE-FAV" id="L-APP-FAV-0" d="M572.475,136.666L625.136,143.769C677.798,150.872,783.12,165.079,835.782,180.694C888.443,196.31,888.443,213.333,888.443,230.357C888.443,247.381,888.443,264.405,888.443,281.429C888.443,298.452,888.443,315.476,888.443,332.5C888.443,349.524,888.443,366.548,889.089,378.359C889.735,390.171,891.028,396.771,891.674,400.07L892.32,403.37"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-PL LE-SONG" id="L-PL-SONG-0" d="M234.364,358.571L234.364,362.738C234.364,366.905,234.364,375.238,234.364,387.917C234.364,400.595,234.364,417.619,234.364,434.643C234.364,451.667,234.364,468.69,271.48,484.084C308.597,499.478,382.83,513.241,419.946,520.123L457.063,527.004"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-HIST LE-SONG" id="L-HIST-SONG-0" d="M555.469,349.506L544.527,355.184C533.585,360.861,511.702,372.216,500.76,386.406C489.819,400.595,489.819,417.619,489.819,434.643C489.819,451.667,489.819,468.69,491.128,480.547C492.438,492.403,495.057,499.091,496.367,502.435L497.676,505.779"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-RT LE-SONG" id="L-RT-SONG-0" d="M471.429,358.571L477.828,362.738C484.226,366.905,497.022,375.238,503.42,387.917C509.819,400.595,509.819,417.619,509.819,434.643C509.819,451.667,509.819,468.69,509.819,480.486C509.819,492.281,509.819,498.848,509.819,502.131L509.819,505.414"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-DB LE-SONG" id="L-DB-SONG-0" d="M756.981,358.571L756.981,362.738C756.981,366.905,756.981,375.238,756.981,387.917C756.981,400.595,756.981,417.619,756.981,434.643C756.981,451.667,756.981,468.69,724.576,483.898C692.172,499.106,627.363,512.497,594.958,519.193L562.554,525.889"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-FAV LE-SONG" id="L-FAV-SONG-0" d="M898.443,460.714L898.443,464.881C898.443,469.048,898.443,477.381,842.472,488.903C786.501,500.425,674.56,515.136,618.589,522.492L562.618,529.847"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-HIST LE-FAV" id="L-HIST-FAV-0" d="M621.016,337.727L668.92,345.368C716.825,353.009,812.634,368.29,859.892,379.231C907.151,390.171,905.859,396.771,905.213,400.07L904.566,403.37"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-CLEAN LE-DB" id="L-CLEAN-DB-0" d="M796.853,256.429L796.853,260.595C796.853,264.762,796.853,273.095,794.143,280.732C791.434,288.369,786.015,295.31,783.306,298.781L780.597,302.251"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-DASH LE-PL" id="L-DASH-PL-0" d="M583.371,237.844L539.955,245.108C496.54,252.372,409.71,266.9,359.838,277.89C309.967,288.879,297.054,296.329,290.597,300.055L284.141,303.78"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-DASH LE-HIST" id="L-DASH-HIST-0" d="M628.114,256.429L628.114,260.595C628.114,264.762,628.114,273.095,625.404,280.732C622.695,288.369,617.276,295.31,614.567,298.781L611.858,302.251"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-DASH LE-RT" id="L-DASH-RT-0" d="M583.371,248.168L569.445,253.712C555.52,259.255,527.669,270.342,508.87,279.524C490.07,288.705,480.321,295.982,475.446,299.62L470.572,303.258"/><path marker-end="url(#mermaid-svg-1754428303498-dbo0r2fa9_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-DASH LE-DB" id="L-DASH-DB-0" d="M672.857,241.073L700.939,247.799C729.022,254.525,785.186,267.977,807.141,278.412C829.095,288.847,816.84,296.266,810.712,299.975L804.585,303.684"/></g><g class="edgeLabels"><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g></g><g class="nodes"><g transform="translate(509.8186378479004, 26.071428298950195)" id="flowchart-UI-885" class="node default uiClass flowchart-label"><rect height="52.14285659790039" width="117.07589721679688" y="-26.071428298950195" x="-58.53794860839844" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-51.03794860839844, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="102.07589721679688"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">User Interface<br />Console Menu</span></div></foreignObject></g></g><g transform="translate(509.8186378479004, 128.2142848968506)" id="flowchart-APP-886" class="node default uiClass flowchart-label"><rect height="52.14285659790039" width="125.3125" y="-26.071428298950195" x="-62.65625" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-55.15625, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="110.3125"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">PlayWiseApp<br />Main Controller</span></div></foreignObject></g></g><g transform="translate(509.8186378479004, 536.7857112884521)" id="flowchart-SONG-887" class="node default coreClass flowchart-label"><rect height="52.14285659790039" width="95.08928680419922" y="-26.071428298950195" x="-47.54464340209961" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-40.04464340209961, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="80.08928680419922"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Song Class<br />Data Model</span></div></foreignObject></g></g><g transform="translate(234.36383819580078, 332.49999809265137)" id="flowchart-PL-888" class="node default coreClass flowchart-label"><rect height="52.14285659790039" width="145.91517639160156" y="-26.071428298950195" x="-72.95758819580078" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-65.45758819580078, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="130.91517639160156"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Playlist<br />Doubly Linked List</span></div></foreignObject></g></g><g transform="translate(588.2421875, 332.49999809265137)" id="flowchart-HIST-889" class="node default coreClass flowchart-label"><rect height="52.14285659790039" width="65.546875" y="-26.071428298950195" x="-32.7734375" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-25.2734375, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="50.546875"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">History<br />Stack</span></div></foreignObject></g></g><g transform="translate(431.3950881958008, 332.49999809265137)" id="flowchart-RT-890" class="node default coreClass flowchart-label"><rect height="52.14285659790039" width="148.14732360839844" y="-26.071428298950195" x="-74.07366180419922" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-66.57366180419922, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="133.14732360839844"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Rating Tree<br />Binary Search Tree</span></div></foreignObject></g></g><g transform="translate(756.981029510498, 332.49999809265137)" id="flowchart-DB-891" class="node default coreClass flowchart-label"><rect height="52.14285659790039" width="118.37053680419922" y="-26.071428298950195" x="-59.18526840209961" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-51.68526840209961, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="103.37053680419922"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Song Database<br />HashMap</span></div></foreignObject></g></g><g transform="translate(45.703125, 230.35714149475098)" id="flowchart-SORT-892" class="node default featureClass flowchart-label"><rect height="52.14285659790039" width="91.40625" y="-26.071428298950195" x="-45.703125" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-38.203125, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="76.40625"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Sorting<br />Algorithms</span></div></foreignObject></g></g><g transform="translate(628.1138401031494, 230.35714149475098)" id="flowchart-DASH-893" class="node default featureClass flowchart-label"><rect height="52.14285659790039" width="89.48661041259766" y="-26.071428298950195" x="-44.74330520629883" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-37.24330520629883, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="74.48661041259766"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Dashboard<br />Analytics</span></div></foreignObject></g></g><g transform="translate(796.8526821136475, 230.35714149475098)" id="flowchart-CLEAN-894" class="node default featureClass flowchart-label"><rect height="52.14285659790039" width="107.99107360839844" y="-26.071428298950195" x="-53.99553680419922" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-46.49553680419922, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="92.99107360839844"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Song Cleaner<br />Duplicates</span></div></foreignObject></g></g><g transform="translate(898.4430847167969, 434.64285469055176)" id="flowchart-FAV-895" class="node default featureClass flowchart-label"><rect height="52.14285659790039" width="131.12723541259766" y="-26.071428298950195" x="-65.56361770629883" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-58.06361770629883, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="116.12723541259766"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Favorites Queue<br />Priority Queue</span></div></foreignObject></g></g></g></g></g></svg>
  </div>
  
  The PlayWise system follows a modular architecture with the following key components:
  - **Core Data Structures**: Song class, Playlist (Doubly Linked List), History (Stack), RatingTree (BST), SongDatabase (HashMap)
  - **Advanced Features**: Sorting algorithms, Dashboard analytics, Song Cleaner, Favorite Songs Queue
  - **Integration Layer**: PlayWiseApp orchestrates all components and provides unified interface
  - **User Interface**: Console-based menu system with comprehensive functionality

- **High-Level Functional Flow**  
  <div align="center">
    <svg aria-roledescription="flowchart-v2" role="graphics-document document" viewBox="-8 -8 1490.4754638671875 162.25" style="max-width: 1490.4754638671875px;" xmlns="http://www.w3.org/2000/svg" width="100%" id="mermaid-svg-1754428303569-f3vzr7gyo"><style>#mermaid-svg-1754428303569-f3vzr7gyo{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:14px;fill:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .error-icon{fill:#5a1d1d;}#mermaid-svg-1754428303569-f3vzr7gyo .error-text{fill:#f97583;stroke:#f97583;}#mermaid-svg-1754428303569-f3vzr7gyo .edge-thickness-normal{stroke-width:2px;}#mermaid-svg-1754428303569-f3vzr7gyo .edge-thickness-thick{stroke-width:3.5px;}#mermaid-svg-1754428303569-f3vzr7gyo .edge-pattern-solid{stroke-dasharray:0;}#mermaid-svg-1754428303569-f3vzr7gyo .edge-pattern-dashed{stroke-dasharray:3;}#mermaid-svg-1754428303569-f3vzr7gyo .edge-pattern-dotted{stroke-dasharray:2;}#mermaid-svg-1754428303569-f3vzr7gyo .marker{fill:#333;stroke:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .marker.cross{stroke:#333;}#mermaid-svg-1754428303569-f3vzr7gyo svg{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:14px;}#mermaid-svg-1754428303569-f3vzr7gyo .label{font-family:"trebuchet ms",verdana,arial,sans-serif;color:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .cluster-label text{fill:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .cluster-label span,#mermaid-svg-1754428303569-f3vzr7gyo p{color:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .label text,#mermaid-svg-1754428303569-f3vzr7gyo span,#mermaid-svg-1754428303569-f3vzr7gyo p{fill:#333;color:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .node rect,#mermaid-svg-1754428303569-f3vzr7gyo .node circle,#mermaid-svg-1754428303569-f3vzr7gyo .node ellipse,#mermaid-svg-1754428303569-f3vzr7gyo .node polygon,#mermaid-svg-1754428303569-f3vzr7gyo .node path{fill:#ffffff;stroke:#333;stroke-width:1px;}#mermaid-svg-1754428303569-f3vzr7gyo .flowchart-label text{text-anchor:middle;}#mermaid-svg-1754428303569-f3vzr7gyo .node .label{text-align:center;}#mermaid-svg-1754428303569-f3vzr7gyo .node.clickable{cursor:pointer;}#mermaid-svg-1754428303569-f3vzr7gyo .arrowheadPath{fill:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .edgePath .path{stroke:#333;stroke-width:2.0px;}#mermaid-svg-1754428303569-f3vzr7gyo .flowchart-link{stroke:#333;fill:none;}#mermaid-svg-1754428303569-f3vzr7gyo .edgeLabel{background-color:#ffffff;text-align:center;}#mermaid-svg-1754428303569-f3vzr7gyo .edgeLabel rect{opacity:0.9;background-color:#ffffff;fill:#ffffff;}#mermaid-svg-1754428303569-f3vzr7gyo .labelBkg{background-color:rgba(255, 255, 255, 0.9);}#mermaid-svg-1754428303569-f3vzr7gyo .cluster rect{fill:rgba(240, 240, 240, 0.8);stroke:#333;stroke-width:1px;}#mermaid-svg-1754428303569-f3vzr7gyo .cluster text{fill:#333;}#mermaid-svg-1754428303569-f3vzr7gyo .cluster span,#mermaid-svg-1754428303569-f3vzr7gyo p{color:#333;}#mermaid-svg-1754428303569-f3vzr7gyo div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:12px;background:#ffffff;border:1px solid #333;border-radius:2px;pointer-events:none;z-index:100;}#mermaid-svg-1754428303569-f3vzr7gyo .flowchartTitleText{text-anchor:middle;font-size:18px;fill:#333;}#mermaid-svg-1754428303569-f3vzr7gyo :root{--mermaid-font-family:"trebuchet ms",verdana,arial,sans-serif;}#mermaid-svg-1754428303569-f3vzr7gyo .inputClass&gt;*{fill:#e8f5e8!important;stroke:#1b5e20!important;stroke-width:2px!important;}#mermaid-svg-1754428303569-f3vzr7gyo .inputClass span{fill:#1b5e20!important;stroke:none!important;}#mermaid-svg-1754428303569-f3vzr7gyo .processClass&gt;*{fill:#e1f5fe!important;stroke:#01579b!important;stroke-width:2px!important;}#mermaid-svg-1754428303569-f3vzr7gyo .processClass span{fill:#01579b!important;stroke:none!important;}#mermaid-svg-1754428303569-f3vzr7gyo .errorClass&gt;*{fill:#ffebee!important;stroke:#c62828!important;stroke-width:2px!important;}#mermaid-svg-1754428303569-f3vzr7gyo .errorClass span{fill:#c62828!important;stroke:none!important;}#mermaid-svg-1754428303569-f3vzr7gyo foreignObject div{font-size:12px!important;line-height:1.2!important;}</style><g><marker orient="auto" markerHeight="12" markerWidth="12" markerUnits="userSpaceOnUse" refY="5" refX="6" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd"><path style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 0 0 L 10 5 L 0 10 z"/></marker><marker orient="auto" markerHeight="12" markerWidth="12" markerUnits="userSpaceOnUse" refY="5" refX="4.5" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointStart"><path style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 0 5 L 10 10 L 10 0 z"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5" refX="11" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303569-f3vzr7gyo_flowchart-circleEnd"><circle style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" r="5" cy="5" cx="5"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5" refX="-1" viewBox="0 0 10 10" class="marker flowchart" id="mermaid-svg-1754428303569-f3vzr7gyo_flowchart-circleStart"><circle style="stroke-width: 1; stroke-dasharray: 1, 0;" class="arrowMarkerPath" r="5" cy="5" cx="5"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5.2" refX="12" viewBox="0 0 11 11" class="marker cross flowchart" id="mermaid-svg-1754428303569-f3vzr7gyo_flowchart-crossEnd"><path style="stroke-width: 2; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 1,1 l 9,9 M 10,1 l -9,9"/></marker><marker orient="auto" markerHeight="11" markerWidth="11" markerUnits="userSpaceOnUse" refY="5.2" refX="-1" viewBox="0 0 11 11" class="marker cross flowchart" id="mermaid-svg-1754428303569-f3vzr7gyo_flowchart-crossStart"><path style="stroke-width: 2; stroke-dasharray: 1, 0;" class="arrowMarkerPath" d="M 1,1 l 9,9 M 10,1 l -9,9"/></marker><g class="root"><g class="clusters"/><g class="edgePaths"><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-INPUT LE-VALID" id="L-INPUT-VALID-0" d="M123.415,91.786L127.582,91.786C131.749,91.786,140.082,91.786,147.532,91.786C154.982,91.786,161.549,91.786,164.832,91.786L168.115,91.786"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-VALID LE-CONTROLLER" id="L-VALID-CONTROLLER-0" d="M301.819,66.466L305.986,64.823C310.153,63.18,318.486,59.894,325.936,58.25C333.386,56.607,339.953,56.607,343.236,56.607L346.519,56.607"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-CONTROLLER LE-COMPONENT" id="L-CONTROLLER-COMPONENT-0" d="M457.21,56.607L461.376,56.607C465.543,56.607,473.876,56.607,481.326,56.607C488.776,56.607,495.343,56.607,498.626,56.607L501.91,56.607"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-COMPONENT LE-OPERATION" id="L-COMPONENT-OPERATION-0" d="M674.554,56.607L678.72,56.607C682.887,56.607,691.22,56.607,698.67,56.607C706.12,56.607,712.687,56.607,715.97,56.607L719.254,56.607"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-OPERATION LE-PROCESS" id="L-OPERATION-PROCESS-0" d="M884.509,33.343L888.676,32.131C892.842,30.919,901.176,28.495,908.626,27.283C916.076,26.071,922.642,26.071,925.926,26.071L929.209,26.071"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-PROCESS LE-DASH" id="L-PROCESS-DASH-0" d="M1071.92,26.071L1079.071,26.071C1086.222,26.071,1100.525,26.071,1113.944,26.071C1127.363,26.071,1139.899,26.071,1146.167,26.071L1152.434,26.071"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;" class="edge-thickness-normal edge-pattern-solid flowchart-link LS-DASH LE-OUTPUT" id="L-DASH-OUTPUT-0" d="M1303.717,26.071L1307.883,26.071C1312.05,26.071,1320.383,26.071,1331.987,31.391C1343.59,36.71,1358.463,47.349,1365.9,52.669L1373.337,57.988"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-VALID LE-OUTPUT" id="L-VALID-OUTPUT-0" d="M289.093,117.857L295.381,121.042C301.669,124.226,314.244,130.595,333.481,133.78C352.718,136.964,378.616,136.964,404.515,136.964C430.413,136.964,456.311,136.964,487.373,136.964C518.434,136.964,554.658,136.964,590.882,136.964C627.106,136.964,663.33,136.964,698.938,136.964C734.546,136.964,769.539,136.964,804.531,136.964C839.524,136.964,874.516,136.964,907.63,136.964C940.744,136.964,971.979,136.964,1006.199,136.964C1040.419,136.964,1077.623,136.964,1115.541,136.964C1153.46,136.964,1192.093,136.964,1227.741,136.964C1263.389,136.964,1296.053,136.964,1318.405,133.451C1340.758,129.938,1352.799,122.912,1358.819,119.399L1364.84,115.885"/><path marker-end="url(#mermaid-svg-1754428303569-f3vzr7gyo_flowchart-pointEnd)" style="fill:none;stroke-width:2px;stroke-dasharray:3;" class="edge-thickness-normal edge-pattern-dotted flowchart-link LS-OPERATION LE-OUTPUT" id="L-OPERATION-OUTPUT-0" d="M884.509,79.871L888.676,81.083C892.842,82.295,901.176,84.719,920.96,85.931C940.744,87.143,971.979,87.143,1006.199,87.143C1040.419,87.143,1077.623,87.143,1115.541,87.143C1153.46,87.143,1192.093,87.143,1227.741,87.143C1263.389,87.143,1296.053,87.143,1315.668,87.143C1335.283,87.143,1341.85,87.143,1345.133,87.143L1348.417,87.143"/></g><g class="edgeLabels"><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel"><g transform="translate(0, 0)" class="label"><foreignObject height="0" width="0"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel"></span></div></foreignObject></g></g><g transform="translate(804.5312652587891, 136.9642848968506)" class="edgeLabel"><g transform="translate(-44.82701110839844, -9.285714149475098)" class="label"><foreignObject height="18.571428298950195" width="89.65402221679688"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel">Invalid Input</span></div></foreignObject></g></g><g transform="translate(1114.8270359039307, 87.14285659790039)" class="edgeLabel"><g transform="translate(-17.907365798950195, -9.285714149475098)" class="label"><foreignObject height="18.571428298950195" width="35.81473159790039"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="edgeLabel">Error</span></div></foreignObject></g></g></g><g class="nodes"><g transform="translate(61.70759201049805, 91.78571367263794)" id="flowchart-INPUT-938" class="node default inputClass flowchart-label"><rect height="52.14285659790039" width="123.4151840209961" y="-26.071428298950195" x="-61.70759201049805" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-54.20759201049805, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="108.4151840209961"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">User Input<br />Menu Selection</span></div></foreignObject></g></g><g transform="translate(1414.0960159301758, 87.14285659790039)" id="flowchart-OUTPUT-939" class="node default inputClass flowchart-label"><rect height="52.14285659790039" width="120.7589340209961" y="-26.071428298950195" x="-60.37946701049805" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-52.87946701049805, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="105.7589340209961"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">User Output<br />Results Display</span></div></foreignObject></g></g><g transform="translate(237.61719512939453, 91.78571367263794)" id="flowchart-VALID-940" class="node default processClass flowchart-label"><rect height="52.14285659790039" width="128.40402221679688" y="-26.071428298950195" x="-64.20201110839844" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-56.70201110839844, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="113.40402221679688"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Input Validation<br />Error Checking</span></div></foreignObject></g></g><g transform="translate(404.51451873779297, 56.60714244842529)" id="flowchart-CONTROLLER-941" class="node default processClass flowchart-label"><rect height="52.14285659790039" width="105.390625" y="-26.071428298950195" x="-52.6953125" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-45.1953125, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="90.390625"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">PlayWiseApp<br />Controller</span></div></foreignObject></g></g><g transform="translate(590.881706237793, 56.60714244842529)" id="flowchart-COMPONENT-942" class="node default processClass flowchart-label"><rect height="52.14285659790039" width="167.34375" y="-26.071428298950195" x="-83.671875" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-76.171875, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="152.34375"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Component Selection<br />Data Structure</span></div></foreignObject></g></g><g transform="translate(804.5312652587891, 56.60714244842529)" id="flowchart-OPERATION-943" class="node default processClass flowchart-label"><rect height="52.14285659790039" width="159.9553680419922" y="-26.071428298950195" x="-79.9776840209961" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-72.4776840209961, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="144.9553680419922"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Data Operation<br />Algorithm Execution</span></div></foreignObject></g></g><g transform="translate(1003.2143096923828, 26.071428298950195)" id="flowchart-PROCESS-944" class="node default processClass flowchart-label"><rect height="52.14285659790039" width="137.4107208251953" y="-26.071428298950195" x="-68.70536041259766" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-61.205360412597656, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="122.41072082519531"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Result Processing<br />State Update</span></div></foreignObject></g></g><g transform="translate(1230.7254753112793, 26.071428298950195)" id="flowchart-DASH-945" class="node default processClass flowchart-label"><rect height="52.14285659790039" width="145.98214721679688" y="-26.071428298950195" x="-72.99107360839844" ry="0" rx="0" style="" class="basic label-container"/><g transform="translate(-65.49107360839844, -18.571428298950195)" style="" class="label"><rect/><foreignObject height="37.14285659790039" width="130.98214721679688"><div style="display: inline-block; white-space: nowrap;" xmlns="http://www.w3.org/1999/xhtml"><span class="nodeLabel">Dashboard Update<br />Analytics</span></div></foreignObject></g></g></g></g></g></svg>
  </div>

**4. Core Feature-wise Implementation**

**Feature:** Song Class (Fundamental Data Model)

- **Scenario Brief**  
  Serves as the foundational data structure for the entire PlayWise system, representing individual music tracks with comprehensive metadata. The Song class encapsulates all essential information including unique identification, track details, rating system, and metadata fields. It acts as the primary data unit that flows through all other components of the system including playlists, databases, trees, and sorting algorithms.

- **Data Structures Used**  
  - std::string for text-based fields (id, title, artist, album, genre, addedDate)
  - int for numerical fields (duration in seconds, rating 1-5 scale)
  - Getter/setter pattern for controlled data access
  - Comparison operators for sorting and searching operations
  - Validation methods for data integrity

- **Time and Space Complexity**  
  - Constructor: O(1) time, O(1) space
  - All getters/setters: O(1) time, O(1) space
  - getDurationString(): O(1) time, O(1) space
  - display(): O(1) time, O(1) space
  - isValid(): O(1) time, O(1) space
  - Comparison operators: O(1) time, O(1) space
  - Overall space complexity: O(1) per song object

- **Sample Input & Output**  
  ```
  Input: 
  - Create song: ID="1", Title="Bohemian Rhapsody", Artist="Queen", Duration=355, Rating=5
  - Set album: "A Night at the Opera"
  - Set genre: "Rock"
  - Get duration string and display
  
  Output: 
  - Song object with all metadata populated
  - Duration string: "5:55"
  - Display: "1. Bohemian Rhapsody by Queen (5:55) - Rating: 5/5 stars"
  - Valid song: true
  ```

- **Code Snippet**  
  ```cpp
  class Song {
  private:
      std::string id;
      std::string title;
      std::string artist;
      int duration;  // in seconds
      int rating;    // 1-5 stars
      std::string album;
      std::string genre;
      std::string addedDate;
  
  public:
      // Constructor with essential parameters
      Song(const std::string& id, const std::string& title, const std::string& artist, 
           int duration, int rating = 0) 
          : id(id), title(title), artist(artist), duration(duration), rating(rating) {}
      
      // Duration formatting for display
      std::string getDurationString() const {
          int minutes = duration / 60;
          int seconds = duration % 60;
          return std::to_string(minutes) + ":" + 
                 (seconds < 10 ? "0" : "") + std::to_string(seconds);
      }
      
      // Data validation
      bool isValid() const {
          return !title.empty() && !artist.empty() && 
                 duration > 0 && rating >= 0 && rating <= 5;
      }
      
      // Comparison for sorting
      bool operator<(const Song& other) const {
          return title < other.title;
      }
  };
  ```

- **Challenges Faced & How You Solved Them**  
  **Data Validation**: Ensuring all song data is valid and consistent across the system. Solved by implementing isValid() method with comprehensive checks for required fields and rating bounds.
  
  **Duration Formatting**: Converting seconds to human-readable MM:SS format. Solved by implementing getDurationString() with proper zero-padding for seconds.
  
  **Memory Efficiency**: Minimizing memory footprint while maintaining functionality. Solved by using appropriate data types and avoiding unnecessary member variables.

**Feature:** Playlist Engine (Doubly Linked List)

- **Scenario Brief**  
  Addresses the critical need for efficient playlist management in modern music applications. The doubly linked list implementation enables bidirectional traversal, allowing users to navigate forward and backward through playlists, move songs between positions, reverse entire playlists, and perform complex reordering operations with minimal memory overhead and optimal performance.

- **Data Structures Used**  
  - Doubly Linked List with head and tail pointers for O(1) insertion/deletion at ends
  - PlaylistNode structure containing Song object, prev pointer, and next pointer
  - Size counter for efficient size queries
  - String-based playlist naming system

- **Time and Space Complexity**  
  - add_song (end): O(1) time, O(1) space
  - add_song_at (position): O(n) time, O(1) space
  - delete_song (by index): O(n) time, O(1) space
  - delete_song_by_id: O(n) time, O(1) space
  - move_song: O(n) time, O(1) space
  - reverse_playlist: O(n) time, O(1) space
  - shuffle: O(n) time, O(n) space
  - display: O(n) time, O(1) space
  - search operations: O(n) time, O(1) space
  - Overall space complexity: O(n) where n is number of songs

- **Sample Input & Output**  
  ```
  Input: 
  - Create playlist "My Favorites"
  - Add songs: "Bohemian Rhapsody" (Queen, 355s), "Hotel California" (Eagles, 391s), "Stairway to Heaven" (Led Zeppelin, 482s)
  - Move song from position 1 to position 3
  - Reverse playlist
  
  Output: 
  - Playlist with 3 songs in reverse order: "Stairway to Heaven", "Bohemian Rhapsody", "Hotel California"
  - Bidirectional navigation enabled
  - Efficient memory usage with O(n) space complexity
  ```

- **Code Snippet**  
  ```cpp
  struct PlaylistNode {
      Song song;
      PlaylistNode* prev;
      PlaylistNode* next;
      
      PlaylistNode(const Song& song) : song(song), prev(nullptr), next(nullptr) {}
  };
  
  void add_song(const std::string& title, const std::string& artist, int duration) {
      std::string id = std::to_string(size + 1);
      Song song(id, title, artist, duration);
      add_song(song);
  }
  
  void add_song(const Song& song) {
      PlaylistNode* newNode = new PlaylistNode(song);
      if (tail == nullptr) {
          head = tail = newNode;
      } else {
          newNode->prev = tail;
          tail->next = newNode;
          tail = newNode;
      }
      size++;
  }
  
  bool move_song(int from_index, int to_index) {
      if (from_index < 0 || from_index >= size || to_index < 0 || to_index >= size) {
          return false;
      }
      
      if (from_index == to_index) return true;
      
      PlaylistNode* fromNode = getNodeAt(from_index);
      Song songToMove = fromNode->song;
      removeNode(fromNode);
      
      PlaylistNode* newNode = new PlaylistNode(songToMove);
      if (to_index == 0) {
          insertNode(newNode, nullptr);
      } else {
          PlaylistNode* afterNode = getNodeAt(to_index - 1);
          insertNode(newNode, afterNode);
      }
      return true;
  }
  ```

- **Challenges Faced & How You Solved Them**  
  **Memory Management**: Dynamic node allocation required careful memory management to prevent leaks. Solved by implementing proper destructor, copy constructor, and assignment operator with deep copying.
  
  **Bidirectional Navigation**: Maintaining prev/next pointers correctly during complex operations was error-prone. Solved by creating helper methods (insertNode, removeNode) that handle pointer updates consistently.
  
  **ID Generation**: Songs added via title/artist needed unique IDs. Solved by implementing sequential ID generation based on playlist size.

**Feature:** Playback History (Stack)

- **Scenario Brief**  
  Implements a sophisticated undo system for recently played songs, allowing users to revert their last played song and re-add it to the current playlist. This feature addresses the common user need to "go back" and replay songs they just listened to, using the LIFO (Last In, First Out) principle to maintain chronological order of playback.

- **Data Structures Used**  
  - std::stack<Song> for LIFO operations with O(1) push/pop
  - Configurable maximum size limit to prevent memory overflow
  - Time-based entry tracking for analytics

- **Time and Space Complexity**  
  - add_played_song: O(1) time, O(1) space
  - undo_last_play: O(1) time, O(1) space
  - get_last_played: O(1) time, O(1) space
  - get_recent_songs: O(n) time, O(n) space
  - clear_history: O(n) time, O(1) space
  - Overall space complexity: O(n) where n is maximum history size

- **Sample Input & Output**  
  ```
  Input: 
  - Play songs: "Song A", "Song B", "Song C", "Song D"
  - Undo last play
  - Get recent songs (last 3)
  
  Output: 
  - History: ["Song A", "Song B", "Song C"] (Song D removed)
  - Last played: "Song C"
  - Recent songs: ["Song C", "Song B", "Song A"]
  ```

- **Code Snippet**  
  ```cpp
  class History {
  private:
      std::stack<Song> playbackHistory;
      int maxSize;
      
  public:
      History(int maxSize = 50) : maxSize(maxSize) {}
      
      void add_played_song(const Song& song) {
          if (playbackHistory.size() >= maxSize) {
              // Remove oldest song if at capacity
              std::stack<Song> temp;
              while (playbackHistory.size() > maxSize - 1) {
                  temp.push(playbackHistory.top());
                  playbackHistory.pop();
              }
              while (!temp.empty()) {
                  playbackHistory.push(temp.top());
                  temp.pop();
              }
          }
          playbackHistory.push(song);
      }
      
      Song undo_last_play() {
          if (playbackHistory.empty()) {
              throw std::runtime_error("No songs in history to undo");
          }
          Song lastSong = playbackHistory.top();
          playbackHistory.pop();
          return lastSong;
      }
      
      std::vector<Song> get_recent_songs(int count) const {
          std::vector<Song> recentSongs;
          std::stack<Song> temp = playbackHistory;
          int limit = std::min(count, static_cast<int>(temp.size()));
          
          for (int i = 0; i < limit; i++) {
              recentSongs.push_back(temp.top());
              temp.pop();
          }
          return recentSongs;
      }
  };
  ```

- **Challenges Faced & How You Solved Them**  
  **Size Management**: Managing stack size limits while maintaining LIFO order was complex. Solved by implementing a size-checking mechanism that removes oldest entries when capacity is reached, using a temporary stack to preserve order.
  
  **Data Retrieval**: Getting recent songs without modifying the stack was challenging. Solved by creating a temporary copy of the stack for traversal operations.

**Feature:** Song Rating Tree (Binary Search Tree)

- **Scenario Brief**  
  Organizes songs by their ratings (1-5 stars) in a BST structure, enabling efficient searching and retrieval of songs by rating ranges. This feature addresses the need for quick access to highly-rated songs, rating-based filtering, and maintaining sorted order for recommendation systems.

- **Data Structures Used**  
  - Binary Search Tree with RatingNode structure
  - Each node contains rating value, vector of songs, and left/right child pointers
  - Inorder traversal for sorted rating access

- **Time and Space Complexity**  
  - insert_song: O(log n) average, O(n) worst case
  - search_by_rating: O(log n) average, O(n) worst case
  - delete_song: O(log n) average, O(n) worst case
  - get_songs_by_rating: O(log n) average, O(n) worst case
  - get_all_songs: O(n) time, O(n) space
  - Overall space complexity: O(n) where n is number of songs

- **Sample Input & Output**  
  ```
  Input: 
  - Songs with ratings: "Song A" (5★), "Song B" (3★), "Song C" (4★), "Song D" (5★), "Song E" (2★)
  - Search for songs with rating 5
  
  Output: 
  - BST structure with rating buckets
  - Rating 5 songs: ["Song A", "Song D"]
  - Efficient search by rating range
  ```

- **Code Snippet**  
  ```cpp
  struct RatingNode {
      int rating;
      std::vector<Song> songs;
      RatingNode* left;
      RatingNode* right;
      
      RatingNode(int rating) : rating(rating), left(nullptr), right(nullptr) {}
  };
  
  class RatingTree {
  private:
      RatingNode* root;
      
  public:
      void insert_song(const Song& song) {
          root = insertNode(root, song.getRating());
          addSongToNode(root, song);
      }
      
      RatingNode* insertNode(RatingNode* node, int rating) {
          if (node == nullptr) {
              return new RatingNode(rating);
          }
          if (rating < node->rating) {
              node->left = insertNode(node->left, rating);
          } else if (rating > node->rating) {
              node->right = insertNode(node->right, rating);
          }
          return node;
      }
      
      std::vector<Song> get_songs_by_rating(int rating) {
          RatingNode* node = findNode(root, rating);
          return node ? node->songs : std::vector<Song>();
      }
      
      std::vector<Song> get_songs_by_rating_range(int minRating, int maxRating) {
          std::vector<Song> result;
          getSongsInRange(root, minRating, maxRating, result);
          return result;
      }
  };
  ```

- **Challenges Faced & How You Solved Them**  
  **Multiple Songs per Rating**: Handling multiple songs with the same rating required storing vectors at each node. Solved by implementing a vector-based storage system within each BST node.
  
  **Range Queries**: Implementing efficient range queries for rating intervals was complex. Solved by implementing inorder traversal with range checking.

**Feature:** Instant Song Lookup (HashMap)

- **Scenario Brief**  
  Provides O(1) average time complexity for song lookups by ID or title, maintaining synchronization with other data structures for consistent data access. This feature addresses the critical need for fast song retrieval in large music libraries, enabling instant search results and efficient playlist management.

- **Data Structures Used**  
  - std::unordered_map for song ID to Song object mapping
  - std::unordered_map for title to song ID mapping
  - Hash-based collision resolution for optimal performance

- **Time and Space Complexity**  
  - insert_song: O(1) average time, O(1) space
  - search_by_id: O(1) average time, O(1) space
  - search_by_title: O(1) average time, O(1) space
  - search_by_artist: O(n) time, O(n) space
  - delete_song: O(1) average time, O(1) space
  - get_all_songs: O(n) time, O(n) space
  - Overall space complexity: O(n) where n is number of songs

- **Sample Input & Output**  
  ```
  Input: 
  - Database with 1000 songs
  - Search for song with ID "song_001" or title "Bohemian Rhapsody"
  
  Output: 
  - Instant retrieval of song object or null if not found
  - O(1) average time complexity regardless of database size
  ```

- **Code Snippet**  
  ```cpp
  class SongDatabase {
  private:
      std::unordered_map<std::string, Song> songsById;
      std::unordered_map<std::string, std::string> titleToId;
      std::unordered_map<std::string, std::vector<std::string>> artistToIds;
      
  public:
      bool insert_song(const Song& song) {
          std::string songId = song.getId();
          if (songsById.find(songId) != songsById.end()) {
              return false; // Song already exists
          }
          songsById[songId] = song;
          titleToId[song.getTitle()] = songId;
          artistToIds[song.getArtist()].push_back(songId);
          return true;
      }
      
      Song* search_by_id(const std::string& songId) {
          auto it = songsById.find(songId);
          return (it != songsById.end()) ? &(it->second) : nullptr;
      }
      
      Song* search_by_title(const std::string& title) {
          auto it = titleToId.find(title);
          if (it == titleToId.end()) return nullptr;
          return search_by_id(it->second);
      }
      
      std::vector<Song> search_by_artist(const std::string& artist) {
          std::vector<Song> result;
          auto it = artistToIds.find(artist);
          if (it != artistToIds.end()) {
              for (const auto& songId : it->second) {
                  Song* song = search_by_id(songId);
                  if (song) result.push_back(*song);
              }
          }
          return result;
      }
  };
  ```

- **Challenges Faced & How You Solved Them**  
  **Data Consistency**: Maintaining consistency between ID and title mappings was challenging. Solved by implementing synchronized update operations that modify all maps simultaneously.
  
  **Artist Search**: Implementing efficient artist-based search required additional data structure. Solved by maintaining a separate map from artist names to song ID lists.

**Feature:** Time-based Sorting

- **Scenario Brief**  
  Implements multiple sorting algorithms (Merge Sort, Quick Sort, Heap Sort) to sort playlists by various criteria including title, duration, rating, artist, and date added. This feature addresses the need for flexible playlist organization and provides users with multiple sorting options for different use cases.

- **Data Structures Used**  
  - std::vector for song storage during sorting
  - std::function for dynamic comparison criteria
  - Lambda expressions for flexible sorting logic

- **Time and Space Complexity**  
  - Merge Sort: O(n log n) time, O(n) space
  - Quick Sort: O(n log n) average, O(n²) worst case, O(log n) space
  - Heap Sort: O(n log n) time, O(1) space
  - Overall: O(n log n) average time complexity

- **Sample Input & Output**  
  ```
  Input: 
  - Unsorted playlist of 100 songs with various titles, durations, ratings
  - Sort by title (A-Z)
  
  Output: 
  - Sorted playlist: "Bohemian Rhapsody", "Hotel California", "Stairway to Heaven"
  - Consistent sorting across all criteria
  ```

- **Code Snippet**  
  ```cpp
  enum class SortCriteria {
      TITLE_ASC, TITLE_DESC, DURATION_ASC, DURATION_DESC,
      RATING_ASC, RATING_DESC, ARTIST_ASC, ARTIST_DESC,
      DATE_ADDED_ASC, DATE_ADDED_DESC
  };
  
  class Sorting {
  public:
      static void mergeSort(std::vector<Song>& songs, SortCriteria criteria) {
          auto compare = getComparator(criteria);
          mergeSortHelper(songs, 0, songs.size() - 1, compare);
      }
      
      static std::function<bool(const Song&, const Song&)> getComparator(SortCriteria criteria) {
          switch (criteria) {
              case SortCriteria::TITLE_ASC:
                  return [](const Song& a, const Song& b) { return a.getTitle() < b.getTitle(); };
              case SortCriteria::DURATION_ASC:
                  return [](const Song& a, const Song& b) { return a.getDuration() < b.getDuration(); };
              case SortCriteria::RATING_ASC:
                  return [](const Song& a, const Song& b) { return a.getRating() < b.getRating(); };
              case SortCriteria::ARTIST_ASC:
                  return [](const Song& a, const Song& b) { return a.getArtist() < b.getArtist(); };
              // ... other criteria
          }
      }
      
  private:
      static void mergeSortHelper(std::vector<Song>& songs, int left, int right, 
                                 const std::function<bool(const Song&, const Song&)>& compare) {
          if (left < right) {
              int mid = left + (right - left) / 2;
              mergeSortHelper(songs, left, mid, compare);
              mergeSortHelper(songs, mid + 1, right, compare);
              merge(songs, left, mid, right, compare);
          }
      }
      
      static void merge(std::vector<Song>& songs, int left, int mid, int right,
                       const std::function<bool(const Song&, const Song&)>& compare) {
          std::vector<Song> temp(right - left + 1);
          int i = left, j = mid + 1, k = 0;
          
          while (i <= mid && j <= right) {
              if (compare(songs[i], songs[j])) {
                  temp[k++] = songs[i++];
              } else {
                  temp[k++] = songs[j++];
              }
          }
          
          while (i <= mid) temp[k++] = songs[i++];
          while (j <= right) temp[k++] = songs[j++];
          
          for (i = 0; i < k; i++) {
              songs[left + i] = temp[i];
          }
      }
  };
  ```

- **Challenges Faced & How You Solved Them**  
  **Flexible Comparison**: Implementing flexible comparison functions for different sorting criteria was complex. Solved by using std::function and lambda expressions to create dynamic comparators.
  
  **Algorithm Selection**: Choosing the right sorting algorithm for different scenarios was challenging. Solved by implementing multiple algorithms and selecting based on data characteristics.

**Feature:** System Snapshot Module (Dashboard)

- **Scenario Brief**  
  Provides real-time monitoring and analytics for the music playlist management system, aggregating data from all components and providing insights into system performance, user behavior, and overall system health. This feature addresses the need for comprehensive system monitoring and user analytics.

- **Data Structures Used**  
  - SystemStats struct for aggregated statistics
  - std::map for organizing statistics by category
  - std::vector for top songs/artists lists
  - Real-time data collection mechanisms

- **Time and Space Complexity**  
  - updateSystemStats: O(n) time, O(n) space
  - display_live_dashboard: O(n) time, O(1) space
  - getTopSongs: O(n log n) time, O(n) space
  - getTopArtists: O(n log n) time, O(n) space
  - getTopGenres: O(n log n) time, O(n) space
  - Overall space complexity: O(n) where n is number of songs

- **Sample Input & Output**  
  ```
  Input: 
  - System with 50 songs, 3 playlists, various ratings and play counts
  - Request dashboard statistics
  
  Output: 
  - Total songs: 50
  - Most played artist: Queen (15 plays)
  - Average rating: 4.2/5
  - Top song: Bohemian Rhapsody (25 plays)
  - System load: 75%
  ```

- **Code Snippet**  
  ```cpp
  struct SystemStats {
      int totalSongs;
      int totalPlaylists;
      int totalPlayTime;
      double averageRating;
      std::string mostPlayedArtist;
      std::string mostPlayedSong;
      int totalPlayCount;
      double systemLoadFactor;
      size_t memoryUsage;
      std::map<std::string, int> artistPlayCounts;
      std::map<std::string, int> genreCounts;
  };
  
  class Dashboard {
  private:
      SystemStats stats;
      SongDatabase* songDatabase;
      std::vector<Playlist*> playlists;
      
  public:
      void updateSystemStats() {
          stats.totalSongs = songDatabase->get_size();
          stats.totalPlaylists = playlists.size();
          stats.averageRating = calculateAverageRating();
          stats.mostPlayedArtist = getMostPlayedArtist();
          stats.mostPlayedSong = getMostPlayedSong();
          stats.totalPlayCount = calculateTotalPlayCount();
          stats.systemLoadFactor = calculateSystemLoad();
          stats.memoryUsage = calculateMemoryUsage();
      }
      
      void display_live_dashboard() const {
          std::cout << "\n=== PLAYWISE SYSTEM DASHBOARD ===" << std::endl;
          std::cout << "Total Songs: " << stats.totalSongs << std::endl;
          std::cout << "Total Playlists: " << stats.totalPlaylists << std::endl;
          std::cout << "Average Rating: " << std::fixed << std::setprecision(1) 
                    << stats.averageRating << "/5" << std::endl;
          std::cout << "Most Played Artist: " << stats.mostPlayedArtist << std::endl;
          std::cout << "Most Played Song: " << stats.mostPlayedSong << std::endl;
          std::cout << "Total Play Count: " << stats.totalPlayCount << std::endl;
          std::cout << "System Load: " << (stats.systemLoadFactor * 100) << "%" << std::endl;
          std::cout << "Memory Usage: " << stats.memoryUsage << " bytes" << std::endl;
          
          displayTopArtists();
          displayTopSongs();
          displayTopGenres();
      }
      
      std::vector<std::string> getTopArtists(int count = 5) const {
          std::vector<std::pair<std::string, int>> artistList;
          for (const auto& pair : stats.artistPlayCounts) {
              artistList.push_back(pair);
          }
          
          std::sort(artistList.begin(), artistList.end(),
                    [](const auto& a, const auto& b) { return a.second > b.second; });
          
          std::vector<std::string> result;
          for (int i = 0; i < std::min(count, static_cast<int>(artistList.size())); i++) {
              result.push_back(artistList[i].first);
          }
          return result;
      }
  };
  ```

- **Challenges Faced & How You Solved Them**  
  **Data Aggregation**: Aggregating data from multiple components while maintaining real-time accuracy was challenging. Solved by implementing efficient update mechanisms and caching strategies.
  
  **Performance Metrics**: Calculating meaningful performance metrics without impacting system performance was complex. Solved by implementing lightweight calculation methods and periodic updates.

**5. Additional Use Case Implementation**

**Use Case:** Auto-Sorting Favorite Songs Queue

- **Scenario Brief**  
  Implements a sophisticated priority queue that automatically maintains songs sorted by listening duration and play count, providing personalized recommendations based on user behavior patterns. This feature addresses the need for intelligent music recommendations and automatic playlist curation.

- **Extension Over Which Core Feature**  
  Extends the basic playlist functionality with intelligent auto-sorting based on user listening patterns, integrating with the History and SongDatabase components.

- **New Data Structures or Logic Used**  
  - std::priority_queue with custom SongWithDuration struct
  - std::unordered_map for tracking listening time and play count
  - Custom comparison operator for multi-level sorting
  - Integration with History component for listening data

- **Sample Input & Output**  
  ```
  Input: 
  - Songs with varying listening times and play counts
  - User plays "Song A" for 300s (3 times), "Song B" for 180s (5 times), "Song C" for 420s (2 times)
  
  Output: 
  - Automatically sorted queue: ["Song B", "Song A", "Song C"]
  - Priority based on total listening time, then play count
  ```

- **Code Snippet**  
  ```cpp
  struct SongWithDuration {
      Song song;
      int totalListeningTime;
      int playCount;
      
      bool operator<(const SongWithDuration& other) const {
          if (totalListeningTime != other.totalListeningTime) {
              return totalListeningTime < other.totalListeningTime;
          }
          if (playCount != other.playCount) {
              return playCount < other.playCount;
          }
          return song.getTitle() > other.song.getTitle();
      }
  };
  
  class FavoriteSongsQueue {
  private:
      std::priority_queue<SongWithDuration> favoritesQueue;
      std::unordered_map<std::string, int> listeningTime;
      std::unordered_map<std::string, int> playCount;
      
  public:
      void addSong(const Song& song, int duration) {
          std::string songId = song.getId();
          listeningTime[songId] += duration;
          playCount[songId]++;
          
          SongWithDuration songWithDuration{song, listeningTime[songId], playCount[songId]};
          updateQueue(songWithDuration);
      }
      
      void syncWithHistory(const std::vector<Song>& recentSongs) {
          for (const auto& song : recentSongs) {
              std::string songId = song.getId();
              if (listeningTime.find(songId) == listeningTime.end()) {
                  listeningTime[songId] = 0;
                  playCount[songId] = 0;
              }
          }
      }
      
      Song getTopFavorite() {
          if (favoritesQueue.empty()) {
              throw std::runtime_error("No favorites available");
          }
          return favoritesQueue.top().song;
      }
      
      std::vector<Song> getTopFavorites(int count) {
          std::vector<Song> result;
          std::priority_queue<SongWithDuration> temp = favoritesQueue;
          
          for (int i = 0; i < count && !temp.empty(); i++) {
              result.push_back(temp.top().song);
              temp.pop();
          }
          return result;
      }
  };
  ```

- **Challenges Faced & Resolution**  
  **Multi-level Sorting**: Implementing multi-level sorting criteria was complex. Resolved by creating a custom comparison operator that prioritizes listening time, then play count, then alphabetical order.
  
  **Data Synchronization**: Keeping the priority queue synchronized with listening data was challenging. Resolved by implementing update mechanisms that rebuild the queue when data changes.

**Use Case:** Duplicate Song Detection and Removal

- **Scenario Brief**  
  Provides comprehensive functionality to detect and remove duplicate songs based on composite keys (song name + artist combination) using HashSet for efficient duplicate checking. This feature addresses data integrity issues and prevents redundant entries in playlists.

- **Extension Over Which Core Feature**  
  Extends the song database functionality with intelligent duplicate detection and cleaning capabilities, integrating with the Playlist and SongDatabase components.

- **New Data Structures or Logic Used**  
  - std::unordered_set for storing unique song keys
  - Composite key generation algorithm
  - String normalization for accurate comparison
  - Batch processing for large datasets

- **Sample Input & Output**  
  ```
  Input: 
  - Playlist with duplicate songs: "Bohemian Rhapsody" (Queen) appears 3 times
  - Request duplicate cleaning
  
  Output: 
  - Cleaned playlist with duplicates removed
  - Report: "2 duplicate songs removed"
  - Maintained data integrity
  ```

- **Code Snippet**  
  ```cpp
  class SongCleaner {
  private:
      std::unordered_set<std::string> uniqueKeys;
      
  public:
      std::string generateCompositeKey(const std::string& title, const std::string& artist) const {
          return normalizeString(title) + "|" + normalizeString(artist);
      }
      
      std::string normalizeString(const std::string& input) const {
          std::string result = input;
          std::transform(result.begin(), result.end(), result.begin(), ::tolower);
          
          // Remove special characters and extra spaces
          std::string cleaned;
          for (char c : result) {
              if (std::isalnum(c) || std::isspace(c)) {
                  cleaned += c;
              }
          }
          
          // Remove extra spaces
          std::string final;
          bool lastWasSpace = true;
          for (char c : cleaned) {
              if (std::isspace(c)) {
                  if (!lastWasSpace) {
                      final += ' ';
                      lastWasSpace = true;
                  }
              } else {
                  final += c;
                  lastWasSpace = false;
              }
          }
          
          // Trim leading/trailing spaces
          if (!final.empty() && final.back() == ' ') {
              final.pop_back();
          }
          
          return final;
      }
      
      std::vector<Song> cleanDuplicates(const std::vector<Song>& songs) {
          std::vector<Song> cleanedSongs;
          uniqueKeys.clear();
          
          for (const auto& song : songs) {
              std::string key = generateCompositeKey(song.getTitle(), song.getArtist());
              if (uniqueKeys.find(key) == uniqueKeys.end()) {
                  uniqueKeys.insert(key);
                  cleanedSongs.push_back(song);
              }
          }
          
          return cleanedSongs;
      }
      
      int getDuplicateCount(const std::vector<Song>& songs) {
          std::unordered_set<std::string> keys;
          int duplicates = 0;
          
          for (const auto& song : songs) {
              std::string key = generateCompositeKey(song.getTitle(), song.getArtist());
              if (keys.find(key) != keys.end()) {
                  duplicates++;
              } else {
                  keys.insert(key);
              }
          }
          
          return duplicates;
      }
  };
  ```

- **Challenges Faced & Resolution**  
  **String Normalization**: Normalizing strings for accurate duplicate detection was challenging. Resolved by implementing case-insensitive string normalization and special character handling.
  
  **Performance Optimization**: Processing large datasets efficiently was important. Resolved by using HashSet for O(1) lookup and implementing batch processing.

**Use Case:** Real-time System Dashboard

- **Scenario Brief**  
  Implements a comprehensive live monitoring and analytics system providing detailed performance metrics, user activity statistics, and system health indicators with real-time updates. This feature addresses the need for system monitoring and user behavior analysis.

- **Extension Over Which Core Feature**  
  Extends the basic dashboard functionality with advanced analytics, real-time monitoring, and comprehensive reporting capabilities.

- **New Data Structures or Logic Used**  
  - Real-time data collection mechanisms
  - Statistical analysis algorithms
  - Performance monitoring systems
  - User behavior tracking

- **Sample Input & Output**  
  ```
  Input: 
  - System running with multiple users and playlists
  - Request comprehensive analytics
  
  Output: 
  - Real-time system statistics
  - User activity patterns
  - Performance metrics
  - System health indicators
  ```

- **Code Snippet**  
  ```cpp
  class AdvancedDashboard : public Dashboard {
  private:
      std::chrono::steady_clock::time_point lastUpdate;
      std::vector<double> performanceHistory;
      std::map<std::string, int> userActivity;
      
  public:
      void updateRealTimeStats() {
          auto now = std::chrono::steady_clock::now();
          auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);
          
          if (timeSinceLastUpdate.count() > 1000) { // Update every second
              updateSystemStats();
              updatePerformanceHistory();
              updateUserActivity();
              lastUpdate = now;
          }
      }
      
      void displayAdvancedMetrics() const {
          display_live_dashboard();
          displayPerformanceTrends();
          displayUserActivity();
          displaySystemHealth();
      }
      
      void displayPerformanceTrends() const {
          std::cout << "\n=== PERFORMANCE TRENDS ===" << std::endl;
          if (performanceHistory.size() >= 2) {
              double currentLoad = performanceHistory.back();
              double previousLoad = performanceHistory[performanceHistory.size() - 2];
              double trend = currentLoad - previousLoad;
              
              std::cout << "Current Load: " << (currentLoad * 100) << "%" << std::endl;
              std::cout << "Trend: " << (trend > 0 ? "+" : "") << (trend * 100) << "%" << std::endl;
          }
      }
      
      void displayUserActivity() const {
          std::cout << "\n=== USER ACTIVITY ===" << std::endl;
          for (const auto& pair : userActivity) {
              std::cout << pair.first << ": " << pair.second << " actions" << std::endl;
          }
      }
  };
  ```

- **Challenges Faced & Resolution**  
  **Real-time Updates**: Implementing real-time updates without impacting system performance was challenging. Resolved by implementing efficient update mechanisms and periodic refresh cycles.
  
  **Data Visualization**: Presenting complex data in a user-friendly format was important. Resolved by creating structured output formats and clear categorization.

**6. Testing & Validation**

| Category                                  | Details |
|-------------------------------------------|---------|
| Number of Functional Test Cases Written   | 59 comprehensive test cases covering all core modules and edge cases |
| Edge Cases Handled                        | Empty playlists, duplicate songs, invalid ratings, memory management, large datasets (1000+ songs), Unicode characters, special characters, negative durations, boundary conditions |
| Known Bugs / Incomplete Features (if any) | None - all core features fully implemented and tested with 100% success rate |

**Test Coverage Details:**
- **Song Class**: 16 test cases covering constructors, setters, duration formatting, rating validation, edge cases
- **Playlist Class**: 19 test cases covering all operations, edge cases, and large datasets
- **Integration Tests**: 9 test cases covering component interactions and workflows
- **Performance Tests**: Multiple test cases with 1000+ songs for scalability validation

**7. Final Thoughts & Reflection**

- **Key Learnings from the Hackathon**  
  This hackathon provided invaluable insights into the practical application of data structures and algorithms in real-world scenarios. I learned the critical importance of choosing appropriate data structures for specific use cases and understanding the trade-offs between time and space complexity. The project demonstrated how fundamental concepts like linked lists, trees, hash maps, and stacks can be combined to create sophisticated systems. I gained deep understanding of system design principles, modular architecture, and the importance of proper memory management in C++. The experience reinforced the value of comprehensive testing and edge case handling in production-ready software.

- **Strengths of Your Solution**  
  The solution demonstrates exceptional modularity with clear separation of concerns, making it highly maintainable and extensible. Each component is optimized for its specific use case while maintaining seamless integration capabilities. The system provides comprehensive functionality with efficient algorithms (O(1) lookups, O(log n) searches, O(n log n) sorting) and proper memory management. The user interface is intuitive with a comprehensive menu system, and the code is well-documented with clear comments and consistent naming conventions. The implementation handles edge cases robustly and includes comprehensive error handling. The test suite provides 100% coverage of all functionality with 59 test cases.

- **Areas for Improvement**  
  The rating tree could benefit from AVL tree balancing to ensure O(log n) worst-case performance instead of potentially degrading to O(n). Advanced caching mechanisms could be implemented for frequently accessed data to improve performance further. Parallel processing could be added for sorting large playlists to leverage multi-core systems. More sophisticated recommendation algorithms based on machine learning could be integrated for better user experience. The system could be extended to support network operations and multi-user scenarios. Additional data visualization features could enhance the dashboard functionality.

- **Relevance to Your Career Goals**  
  This project demonstrates strong fundamentals in data structures and algorithms, system design, and C++ programming - all essential skills for backend development, system programming, and software engineering roles. The modular architecture and performance optimization skills are directly applicable to large-scale software development projects. The experience with testing frameworks and quality assurance practices is valuable for any software development role. The project showcases problem-solving abilities, attention to detail, and the ability to work with complex systems - all highly sought-after skills in the technology industry. This work aligns perfectly with career goals in software engineering, backend development, and system architecture.