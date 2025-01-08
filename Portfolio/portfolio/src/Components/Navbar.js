import React, { useEffect } from 'react';
import '../index.css';

function Navbar() {
  useEffect(() => {
    const handleScroll = () => {
      const nav = document.querySelector('nav');
      if (window.scrollY > 500) {
        nav.classList.add('navbar-scrolled');
      } else {
        nav.classList.remove('navbar-scrolled');
      }
    };

    window.addEventListener('scroll', handleScroll);

    return () => {
      window.removeEventListener('scroll', handleScroll);
    };
  }, []);

  return (
    <nav>
      <div className='profile'>
        <a className="navbar-title" href='#home'>SHAUN JACOB</a>
      </div>
      <div className='options'>
        <a href="#about">About</a>
        <a href="#skills">Skills</a>
        <a href="#contacts">Contacts</a>
      </div>
    </nav>
  );
}

export default Navbar;
