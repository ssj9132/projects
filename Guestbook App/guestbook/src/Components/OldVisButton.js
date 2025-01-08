import React from 'react';
import { Link } from 'react-router-dom';
import OldVisImg from '../Assets/OldVisImg.png';

const OldVisButton = () => {
  return (
    <Link to="/searchbook" className="oldvis-button">
      <img src={OldVisImg} alt="OldVis" className="old-vis" />
    </Link>
  );
};

export default OldVisButton;
