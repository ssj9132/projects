import React from 'react';
import { Link } from 'react-router-dom';
import NewVisImg from '../Assets/NewVisImg.png';

const NewVisButton = () => {
  return (
    <Link to="/registration" className="newvis-button">
      <img src={NewVisImg} alt="NewVis" className="new-vis" />
    </Link>
  );
};

export default NewVisButton;
