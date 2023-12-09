import cv2

# Initialisation de l'algorithme ORB
orb = cv2.ORB_create()

# Initialisation du détecteur et du descripteur ORB
bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

# Capturer la vidéo (ou lire un flux de données de la caméra)
cap = cv2.VideoCapture(0)

# Initialisation de la carte
map_points = []
keypoints_map = []
descriptors_map = []

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Trouver les points clés et les descripteurs de l'image capturée
    kp_frame, des_frame = orb.detectAndCompute(frame, None)

    # Matcher les descripteurs de l'image capturée avec ceux de la carte
    if descriptors_map:
        matches = bf.match(descriptors_map[-1], des_frame)
        matches = sorted(matches, key=lambda x: x.distance)

        # Obtenir les points correspondants
        matched_points = [keypoints_map[-1][m.trainIdx].pt for m in matches]

        # Ajouter les nouveaux points à la carte
        map_points.extend(matched_points)
        keypoints_map.append(kp_frame)
        descriptors_map.append(des_frame)
    else:
        # Première image : initialiser la carte
        keypoints_map.append(kp_frame)
        descriptors_map.append(des_frame)
        map_points = [p.pt for p in kp_frame]

    # Dessiner les points sur l'image
    for point in map_points:
        cv2.circle(frame, tuple(map(int, point)), 2, (0, 255, 0), -1)

    cv2.imshow('SLAM', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()