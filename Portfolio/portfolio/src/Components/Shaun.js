import React from 'react';
import Glasses from '../Assets/glassesGuy.gif';
import '../index.css'; 
import ConnectButton from './ConnectButton';
import ResumeButton from './ResumeButton';

const Intro = () => {
    return (
      <div className='intro'>
        <div className='text-container'>
          <h1>Welcome to my page!</h1>
          <h5>A college junior with a versatile background in Web and Software Development, Embedded Systems, and Networks Engineering.</h5>
          <div className='buttons'>
          <ConnectButton /> 
          <ResumeButton />
          </div>
        </div>
        <div className='image-container'>
          <img src={Glasses} alt="Glasses Guy" />
        </div>
        
      </div>
    );
};

export default Intro;
