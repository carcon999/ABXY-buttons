## Assembly Instructions

To build the device, you’ll need to gather the required tools and parts, and modify parts of the four-button case.

### Required Tools

| Image | Tool | Purpose | Notes |
|-------|------|---------|-------|
| <img src="../image/MAKE/driver.jpg" width="128"> | Small Phillips screwdriver | Fastening the case screws | - |
| <img src="../image/MAKE/drill.jpg" width="128"> | 3mm hand drill | Drilling the LED opening | - |
| <img src="../image/MAKE/knife.jpg" width="128"> | Precision knife | Modifying the case | - |
|  | Work gloves | Preventing injury while using the knife | - |

### Required Parts

| Image | Name | Description | Notes |
|--------|------|-------------|-------|
| <img src="../image/MAKE/4-button-case.jpg" width="128"> | (A1) 4-button case | Either SF or SNES version | Obtain from flea markets, as the gacha sale has ended |
| <img src="../image/MAKE/assembled-board.jpg" width="128"> | (A2) Assembled PCB | Created from design files | - |
| <img src="../image/MAKE/inner.jpg" width="128"> | (A3) Inner lid for PCB | 3D printed | [ABXY-Inner.stl](./3d-model/ABXY-Inner.stl) |
| <img src="../image/MAKE/led3mm-point.jpg" width="128"> | (A4) LED alignment plate | 3D printed | [LED-3mmPoint.stl](./3d-model/ABXY-Inner.stl) |
| <img src="../image/MAKE/ripo-battery.jpg" width="128"> | (A5) Lithium-ion polymer battery | Fits inside the case (35x20x5mm) | 300mAh |
| <img src="../image/MAKE/clear-soft.jpg" width="128"> | (A6) Clear soft plastic rod (3mm) | Used to extend LED light | Cut to 6mm length |
| <img src="../image/MAKE/usb-type-c.jpg" width="128"> | (A7) USB Type-C cable | For charging and programming | - |
| <img src="../image/MAKE/cushion-seal.jpg" width="128"> | (A8) Cushion seal | Prevents battery from rattling | Optional if not needed |

### Disassembling the Case

Remove the four screws. Inside, there is a plastic inner lid, but it will not be used for this build. The ball chain should also be temporarily removed as it gets in the way during assembly. All other parts, including the four screws, will be reused, so take care not to lose them. The rubber switch is prone to attracting dust, so handle it carefully.

| Image | Part Name | Notes |
|--------|-----------|--------|
| <img src="../image/MAKE/case-top.jpg" width="128"> | (B1) Top case | Requires modification |
| <img src="../image/MAKE/case-bottom.jpg" width="128"> | (B2) Bottom case | Requires modification |
| <img src="../image/MAKE/inner-original.jpg" width="128"> | (B3) Original inner lid | Not used |
| <img src="../image/MAKE/rubber-switch.jpg" width="128"> | (B4) Rubber switch | Handle carefully to avoid dust contamination |
| <img src="../image/MAKE/4-buttons.jpg" width="128"> | (B5) Buttons (4 pieces) | - |
| <img src="../image/MAKE/4-screw.jpg" width="128"> | (B6) Screws (4 pieces) | Small—easy to lose |
| <img src="../image/MAKE/ball-chain.jpg" width="128"> | (B7) Ball chain | Remove for the assembly process |

### Work Overview

The build process involves modifications to three main areas of the case, followed by final assembly.  
Please take care when using knives or other sharp tools to avoid injury.

| Image | Task |
|--------|------|
| <img src="../image/MAKE/slide-switch-hole.jpg" width="256"> | 1. Modify the slide switch area |
| <img src="../image/MAKE/usb-hole.jpg" width="256"> | 2. Modify the USB connector opening |
| <img src="../image/MAKE/led-hole.jpg" width="256"> | 3. Drill the LED window |
| <img src="../image/MAKE/stick-6mm.jpg" width="256"> | 4. Cut the clear plastic rod |
| <img src="../image/MAKE/assemble.jpg" width="256"> | 5. Final assembly |

### 1. Modifying the Slide Switch Area

| Image | Description |
|-------|-------------|
| <img src="../image/MAKE/slide-switch-pos.jpg" width="512"> | When fitting the (A2) assembled PCB into the unmodified (B1) top case, the slide switch will interfere, preventing it from seating properly. The goal is to trim this area so the PCB fits cleanly. The length of the area to be removed is about 12 mm, as indicated by the red dashed lines in the image. Mark two points where the dashed line intersects with the (B1) top case using a knife. |
| <img src="../image/MAKE/slide-switch-cut.jpg" width="512"> | In the photo, the upper case in the top row is unmodified, while the lower row shows it after modification. Using the marks you made earlier, slowly shave away material to a depth of about 3 mm. |
| <img src="../image/MAKE/slide-switch-flat.jpg" width="512"> | As a guide, 3 mm depth is where the surface of the slide switch becomes level with the top edge of the case when the (A2) assembled PCB is inserted into the (B1) top case (see red dashed line). <br>**Note:** When checking fit, be sure to also insert the (B4) rubber switch, as the rubber's thickness must be accounted for. |
| <img src="../image/MAKE/slide-switch-bottom.jpg" width="512"> | Fit the (B2) bottom case to the (B1) top case and mark the cutting position on the bottom case. As before, trim the (B2) bottom case to the same depth. |
| <img src="../image/MAKE/slide-switch-bottom-cut.jpg" width="512"> | The depth to cut here is about 1.4 mm — just the interlocking portion of the case. Compared to the top case modification, this is thinner and easier to work with. |
| <img src="../image/MAKE/slide-switch-hole.jpg" width="512"> | Completed modification. |

### 2. Modifying the USB Connector Opening

| Image | Description |
|-------|-------------|
| <img src="../image/MAKE/usb-pos.jpg" width="256"> | The USB opening modification process is similar to the slide switch modification above. Fit the (A2) assembled PCB into the (B1) top case, and mark two points that extend from the USB connector position. The distance is about 9 mm. |
| <img src="../image/MAKE/usb-top.jpg" width="256"> | The cutting depth is about 2.5 mm. |
| <img src="../image/MAKE/usb-no-flat.jpg" width="256"> | Unlike the slide switch modification, the USB connector will not be flush with the case surface. Check the depth while working, together with the modification on the (B2) bottom case. |
| <img src="../image/MAKE/usb-result.jpg" width="256"> | Fit the (B2) bottom case to the (B1) top case and mark the cutting position on the bottom case. As before, cut the (B2) bottom case to the same depth. |
| <img src="../image/MAKE/usb-bottom.jpg" width="256"> | The cutting depth here is about 1.4 mm — just the interlocking portion of the case. |
| <img src="../image/MAKE/usb-hole.jpg" width="256"> | Completed modification. |

### 3. Modifying the LED Window

| Image | Description |
|-------|-------------|
| <img src="../image/MAKE/led-hole-plate.jpg" width="256"> | Drill a 3 mm hole in the (B1) top case to allow the LED light from the PCB to be visible from the outside. The hole must be aligned with the LED position on the PCB, so use the (A4) LED alignment plate as shown in the photo to avoid misalignment. The small protrusion should be visible at the upper left. |
| <img src="../image/MAKE/led-hole-plate-drill.jpg" width="256"> | Use a 3 mm hand drill to make the hole. Do not force the drill through in one go — proceed gradually, clearing away shavings as you work. |
| <img src="../image/MAKE/led-hole-result.jpg" width="256"> | Just before breaking through, you will encounter a decorative film layer about 0.5 mm thick that differs from the main material. Drill through it slowly to ensure a clean finish. |

*Once the hole is complete, the (A4) LED alignment plate is no longer needed.*

### 4. Cutting the Clear Plastic Rod

| Image | Description |
|-------|-------------|
| <img src="../image/MAKE/stick-6mm.jpg" width="256"> | Cut the (A6) clear soft plastic rod (3 mm diameter) to a length of about 6 mm. Being slightly shorter is not an issue, but if it is too long, it will protrude from the (B1) top case, so adjust accordingly. |

### 5. Assembly

| Image | Description |
|-------|-------------|
| <img src="../image/MAKE/asm-step1.jpg" width="256"> | Insert the 6 mm cut (A6) clear plastic rod into the LED hole drilled earlier in the (B1) top case. Since it’s a 3 mm rod through a 3 mm hole, it will be a tight fit — adjust as necessary. Ensure it is flush with the case surface so it doesn’t protrude. |
| <img src="../image/MAKE/asm-step2.jpg" width="256"> | Insert the (B5) buttons (4 pieces) into the (B1) top case. |
| <img src="../image/MAKE/asm-step3.jpg" width="256"> | Place the (B4) rubber switch over the buttons. There is no top/bottom orientation for this part. |
| <img src="../image/MAKE/asm-step4.jpg" width="256"> | Fit the (A2) assembled PCB into the (B1) top case. The fit around the top-right LED position may be tight, so adjust if necessary. Likewise, if the USB or slide switch openings are insufficiently trimmed, shave them further as needed. |
| <img src="../image/MAKE/asm-step5.jpg" width="256"> | Pass the connector of the (A5) lithium-ion polymer battery through the open section of the (A3) PCB inner lid. |
| <img src="../image/MAKE/asm-step6.jpg" width="256"> | Connect the battery connector to the receiving connector on the (A2) assembled PCB. Ensure correct orientation. The LED will light red — long press the slide switch for 1 second to turn the power OFF (LED off). Route the cable as shown in the photo, behind the round section, to avoid pinching and breaking the wire. <br>**Note:** Even when the LED is off, the device is still in low-power mode, so avoid dropping metal objects (like screws) onto it. |
| <img src="../image/MAKE/asm-step7.jpg" width="256"> | Attach the (A8) cushion seal (with one side still covered) to the underside of the central upper post of the (B2) bottom case. This helps prevent battery movement. If rattling becomes an issue later, you can fully stick it in place. The example in the photo uses it with the adhesive side still covered. |
| <img src="../image/MAKE/asm-step8.jpg" width="256"> | Finally, align everything carefully and fasten with the four screws. The fit should be precise, but if the halves do not align well, check for interference — common issues are insufficient trimming of the USB or slide switch openings, preventing the PCB from seating properly. Rework as needed. Done! |

For instructions on how to use the device, see [HOW_TO_USE.en.md](../document/HOW_TO_USE.en.md).

[Back](../README.en.md)
